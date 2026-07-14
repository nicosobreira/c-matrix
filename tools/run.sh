#!/usr/bin/env bash

set -eou pipefail

BUILD="./build"

function binary_path()
{
	local preset="$1"

    echo "${BUILD}/${preset}/examples/example"
}

function run_workflow()
{
	local workflow="$1"

	cmake --workflow --preset "$workflow"
}

function run_debug()
{
	run_workflow "dev"

	local binary
	binary=$(binary_path "debug")

	if [[ -n "${TMUX-}" ]]; then
		local port
		port=$(shuf -i 2000-65000 -n 1)

		echo "Starting gdbserver on port ${port}..."

		tmux split-window -h -p 50 \
			"exec gdbserver :${port} '${binary}'"

		# Small delay so gdbserver is listening
		sleep 0.2

		tmux select-pane -t left

		gdb --tui -q \
			-ex "file ${binary}" \
			-ex "target remote :${port}"
	else
		gdb --tui -q "${binary}"
	fi
}

function run_test()
{
	run_workflow "test"

    link_compile_commands "debug"
}

function run_benchmarks()
{
    local bench_binary="$1"

    run_workflow "bench"

    if [[ -z "$bench_binary" ]]; then
        return
    fi

    local path="${BUILD}/benchmark/benchmarks/${bench_binary}"
    if [[ -f "$path" ]]; then
        exec "$path"
    fi

    echo "Benchmark \"${path}\" doens't exist"
}

function link_compile_commands()
{
    local preset="$1"

    local link="${BUILD}/compile_commands.json"
    if [[ ! -f "${link}" ]]; then
        echo "Linking compile_commands ..."

        local src="./${preset}/compile_commands.json"
        (cd "${BUILD}" && ln -s "${src}" .)
    fi
}

function run()
{
	run_workflow "dev"

    link_compile_commands "debug"

	exec "$(binary_path "debug")"
}

MODE="${1-}"
OPT="${2-}"

case "$MODE" in
	debug | d)
		echo -e "\tDebug\n"
		run_debug
		;;
	build)
		echo -e "\tBuild\n"
		run_workflow "dev"
		;;
	test | t)
		echo -e "\tTest\n"
		run_test
		;;
	bench)
		echo -e "\tBenchmarks\n"
		run_benchmarks "$OPT"
		;;
	run | r)
		run
		;;
	*)
		run
		;;
esac
