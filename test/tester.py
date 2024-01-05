#!/usr/bin/python3
from subprocess import Popen, PIPE, STDOUT
import random
import itertools

def random_str(chars):
    chars_qty = len(chars)
    res = ""
    for _ in range(random.randint(0, 20)):
        res += chars[random.randint(0, chars_qty - 1)]
    return (res)

def random_cmds(token_qty):
    tokens = ["echo", '"', "'", "&&", "||", ">", "<", ">>", "<<", "|", "$", "(", ")"]
    tokens += [" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "]
    res = [""]
    res += list(map(lambda x: "".join(list(x)), itertools.product(tokens, repeat=token_qty)))
    random.shuffle(res)
    return (res)

tests = ["echo hi\necho ho"]
tests.append("|| echo")
tests.append("echo ||")
tests.append("a|| >")
tests.append("a|| >          e")
tests.append("a||>e")
tests.append("(e)")
tests.append("((e)")
tests.append("( ( ( )   (e)            ))")
tests.append("( ( (   (e)            )))")
tests.append("( ( (   (e)      |      )))")
tests.append("echo (ok)")
tests.append("echo ok (> o)")
tests.append("(echo) ok > o")
tests.append("(e)(a)")
tests.append("echo ok > (o)")
tests.append("(echo ok) > o")
tests.append("(<o cat)")
tests.append("e && ((e))")
tests.append("e && (e)")
tests.append("(e &&) (e)")
tests.append("echo hi | cat -e")
tests.append("A=45\necho $A")
tests.append("export cheval=600\necho $cheval")
tests.append("echo allo > out.txt && echo allo2 >> out.txt && cat out.txt")
tests.append("echo PAPA > out.txt\ncat out.txt")
tests.append("echo ok > bad\ncat \"bad file\"\necho $?")
tests.append("echo tarantule > out.txt\ncat < out.txt")
tests.append("unset PATH\ncat")
tests.append("export PATH=\ncat")
tests.append("echo \"hello | cat -e\"")
tests.append("echo 'hello | cat -e'")
tests.append("4VAR=4")
tests.append("VAR=4\necho ok\"ok$VARok\"")
tests.append("VAR=4\necho ok\"ok$VAR ok\"")
tests.append("echo -n sdfsdfsdgsdg")
tests.append("echo -n sdfsdfsdgsdg | cat -e | cat -e |cat -e|cat -e")
tests.append("\n\n")
tests.append("              \n           \n\n      \n")
tests.append("echo | ")
tests.append("| echo |   |")
tests.append("|||||||||")
tests.append("<")
tests.append(">")
tests.append(">>")
tests.append("<<")
tests.append("<<<") # devrait pas faire 2 heredoc
tests.append('unset PATH\ncat\nexport PATH="/bin"\ncat')

# ECHO TESTS
tests.append('echo test tout')
tests.append('echo test      tout')
tests.append('echo -n test tout')
tests.append('echo -n -n -n test tout')


# CD TESTS
tests.append('cd .. \n pwd')
tests.append('cd /Users \n pwd')
tests.append('cd \n pwd')
tests.append('mkdir test_dir \n cd test_dir \n rm -rf ../test_dir \n cd . \n pwd \n cd . \n pwd \n cd .. \n pwd')


# PIPE TESTS
tests.append('cat tests/lorem.txt | grep arcu | cat -e')
# tests.append('echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e')
tests.append('cat /dev/random | head -c 100 | wc -c')
# tests.append('ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls')
# tests.append('ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls')

# ENV EXPANSIONS + ESCAPE
tests.append('echo test     \    test')
tests.append('echo \"test')
tests.append('echo $TEST')
tests.append('echo "$TEST"')
tests.append("echo '$TEST'")
tests.append('echo "$TEST$TEST$TEST"')
tests.append('echo "$TEST$TEST=lol$TEST"')
tests.append('echo "   $TEST lol $TEST"')
tests.append('echo $TEST$TEST$TEST')
tests.append('echo $TEST$TEST=lol$TEST""lol')
tests.append('echo    $TEST lol $TEST')
tests.append('echo test "" test "" test')
tests.append('echo "\$TEST"')
tests.append('echo "$=TEST"')
tests.append('echo "$"')
tests.append('echo "$?TEST"')
tests.append('echo $TEST $TEST')
tests.append('echo "$1TEST"')
tests.append('echo "$T1TEST"')

# ENV EXPANSIONS
ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
tests.append('export =')
tests.append('export 1TEST= \n' + ENV_SHOW)
tests.append('export TEST \n' + EXPORT_SHOW)
tests.append('export ""="" \n ' + ENV_SHOW)
tests.append('export TES=T="" \n' + ENV_SHOW)
tests.append('export TE+S=T="" \n' + ENV_SHOW)
tests.append('export TEST=LOL \n echo $TEST \n' + ENV_SHOW)
tests.append('export TEST=LOL \n echo $TEST$TEST$TEST=lol$TEST')
tests.append('export TEST=LOL\n export TEST+=LOL \n echo $TEST \n' + ENV_SHOW)
tests.append(ENV_SHOW)
tests.append(EXPORT_SHOW)
tests.append('export TEST="ls       -l     - a" \n echo $TEST \n $LS \n ' + ENV_SHOW)

# REDIRECTIONS
tests.append('echo test > ls \n cat ls')
tests.append('echo test > ls >> ls >> ls \n echo test >> ls\n cat ls')
tests.append('> lol echo test lol\n cat lol')
tests.append('>lol echo > test>lol>test>>lol>test mdr >lol test >test\n cat test')
tests.append('cat < ls')
tests.append('cat < ls > ls')

# MULTI TESTS
tests.append('echo testing multi \n echo "test 1 \n | and 2" \n cat tests/lorem.txt | grep Lorem')

# SYNTAX ERROR
tests.append('\n\n test')
tests.append('| test')
tests.append('echo > <')
tests.append('echo | |')
tests.append('<')

# EXIT
tests.append("exit 42")
tests.append("exit 42 53 68")
tests.append("exit 259")
tests.append("exit 9223372036854775807")
tests.append("exit -9223372036854775808")
tests.append("exit 9223372036854775808")
tests.append("exit -9223372036854775810")
tests.append("exit -4")
tests.append("exit wrong")
tests.append("exit wrong_command")
tests.append("gdagadgag")
tests.append("ls -Z")
tests.append("cd gdhahahad")
tests.append("ls -la | wtf")

tests.append("<<<<") # devrait       "
tests.append("<$<")
tests.append("cat<<eof|cat -b\nsalut\neof")
tests.append("exit")
tests += random_cmds(4)

# --------------------------------------------------------
NAME = "../minishell"
MSG_ERROR = f"{'Error:':30}" + "{}\n  " + f"{'expected:':28}" + "{}\n  " + f"{'got:':28}" + "{}"
PRINT_SUCCESS = 1
LEAK_MINISHELL = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions=../vg_suppress.txt ../minishell"

def filter_output(output, input):
    output_lines = output.split("\n")
    input_lines = input.split("\n")
    input_lines += list(map(lambda line: "> " + line, input_lines)) # this way, heredoc lines will be ignored
    output_lines = list(filter(lambda line: line not in input_lines, output_lines)) # ignore lines from input
    return "\n".join(output_lines)

def get_output(cmd, input):
    p = Popen(cmd.split(" "), stdout=PIPE, stdin=PIPE, stderr=STDOUT)  
    grep_stdout = p.communicate(input=bytes(input, "utf8"))[0]
    return filter_output(grep_stdout.decode(), input)

def get_outputs(input):
    return [get_output("bash", input), get_output("../minishell", input)]

def assert_fd_leak(lines):
    qty = len(lines)
    for i in range(qty):
        if ("Open file descriptor" in lines[i]):
            if (i < qty - 1 and "inherited from parent" not in lines[i + 1]):
                return False
    return True

def assert_leaks(input):
    output = get_output(LEAK_MINISHELL, input)
    lines = output.split("\n")
    last_line = lines[-1]
    if (not len(last_line)):
        last_line = output.split("\n")[-2]
    res = last_line.split(" ")[3] == "0" #and assert_fd_leak(lines)
    return (res, output)

def result_differs(res):
    if res[0].startswith("bash") and res[1].startswith("minishell"):
        res[0] = res[0][4:]
        res[1] = res[1][9:]
    if res[0].startswith(": line "):
        i = 7
        while (res[0][i].isdigit()):
            i += 1
        res[0] = res[0][i:]
    return (res[0] != res[1])

if __name__ == "__main__":
    for test in tests:
        res = assert_leaks(test)
        if (not res[0]):
            print(res[1], "\nLEAK:", test)
            break
        res = get_outputs(test)
        if (result_differs(res)):
            print(MSG_ERROR.format(test, res[0], res[1]), end="\n----------\n")
        elif PRINT_SUCCESS:
            print("----", res[0], res[1], "----", sep="\n")
