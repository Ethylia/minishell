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

# tests.append("<<<<") # devrait       "
# tests.append("<$<")
# tests.append("cat<<eof|cat -b\nsalut\neof")
# tests += random_cmds(4)

# --------------------------------------------------------
NAME = "../minishell"
MSG_ERROR = f"{'Error:':30}" + "{}\n  " + f"{'expected:':28}" + "{}\n  " + f"{'got:':28}" + "{}"
PRINT_SUCCESS = 1
LEAK_MINISHELL = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=../vg_suppress.txt ../minishell"

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

def assert_leaks(input):
    output = get_output(LEAK_MINISHELL, input)
    last_line = output.split("\n")[-1]
    if (not len(last_line)):
        last_line = output.split("\n")[-2]
    res = last_line.split(" ")[3] == "0"
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
