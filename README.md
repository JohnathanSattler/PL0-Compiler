# PL/0 Compiler

Compiling:
----------

Compile compiler: `make`

Compile vm: `gcc -o vm vm.c`

Executing:
----------

run compiler: `./compile (arguments) (input) (output)`

run vm: `./vm (input)`

Arguments:

* `--source` Display input PL/0 code
* `--clean` Display input PL/0 Code without comments
* `--tokens` Display tokens found from lexer
* `--pm0` Display PM/0 code generated from parser

Examples:
---------

Compiler: `./compile input.pl0 output.pm0`

Compiler with arguments: `./compile --source --clean --tokens --pm0 input.pl0 output.pm0`

Virtual Machine: `./vm output.pm0`
