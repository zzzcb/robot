#! /usr/bin/env python
# coding:utf8
import re 

def search_print(re_search_ret):
    if re_search_ret:
        print(re_search_ret.group())
        print(re_search_ret.start())
        print(re_search_ret.end())
        print("=============")

if __name__ == "__main__":

    # 1 . 点 : 在默认模式，匹配除了换行的任意字符。如果指定了 re.DOTALL ，它将匹配包括换行符的任意字符
    if 0 == 1:
        pattern = re.compile(".")
        search_print(pattern.search("helloworld")) #  h
        search_print(pattern.search("\nhelloworld")) # h

        pattern = re.compile(".",re.DOTALL)
        search_print(pattern.search("\nhelloworld")) # \n



    # 2 ^  异或符号 : 匹配字符串的开头， 并且在 MULTILINE 模式也匹配换行后的首个符号。
    if 0 == 1:
        pattern = re.compile("^h")
        search_print(pattern.search("helloworld")) #  h
        search_print(pattern.search("ooo\nhelloworld")) #  None

        pattern = re.compile("^h",re.MULTILINE)
        search_print(pattern.search("ooo\nhelloworld")) #  h


    # 3 $ 美元符 | 匹配字符串尾或者在字符串尾的换行符的前一个字符，在 MULTILINE 模式下也会匹配换行符之前的文本。
    if 0 == 1:
        pattern = re.compile("foo")
        search_print(pattern.search("foo")) #  foo
        search_print(pattern.search("foobar")) #  foo

        pattern = re.compile("foo$")
        search_print(pattern.search("foo")) #  foo
        search_print(pattern.search("foobar")) #  None

        print("===============================")

        pattern1 = re.compile("foo.$")
        pattern2 = re.compile("foo.$",re.MULTILINE)
        search_print(pattern1.search("foo1\nfoo2\n")) #  foo2
        search_print(pattern2.search("foo1\nfoo2\n")) #  foo1

    # 4 * 星号: 对它前面的正则式匹配0到任意次， 尽量多的匹配字符串,贪婪
    if 0 == 1:
        pattern = re.compile("ab*") # * 前面的正则表达式是 b 
        search_print(pattern.search("a")) #  a
        search_print(pattern.search("ab")) # ab
        search_print(pattern.search("abbb")) # abbb
        search_print(pattern.search("abbc")) # abb


    # 5 + 加号: 对它前面的正则式匹配1到任意次,尽量多的匹配字符串,贪婪
    if 0 == 1:
        pattern = re.compile("ab+") # + 前面的正则表达式是 b 
        search_print(pattern.search("a")) #  None
        search_print(pattern.search("ab")) # ab
        search_print(pattern.search("abbb")) # abbb
        search_print(pattern.search("abbc")) # abb

    # 6 ? 问号: 对它前面的正则式匹配0到1次,尽量多的匹配字符串,贪婪
    if 0 == 1:
        pattern = re.compile("ab?") # ? 前面的正则表达式是 b 
        search_print(pattern.search("a")) #  a
        search_print(pattern.search("ab")) # ab
        search_print(pattern.search("abbb")) # ab
        search_print(pattern.search("abbc")) # ab

    # 7 修饰符后加 ? : 默认下,'*', '+'，和 '?' 修饰符都是 贪婪的；它们在字符串进行尽可能多的匹配,这三个修饰符后加？就是非贪婪了
    # *? +? ??  非贪婪指的是以尽量少的字符被匹配
    if 0 == 1:
        pattern1 = re.compile("ab*")# 这里的* 是贪婪的
        pattern2 = re.compile("ab*?")# 这里的* 是非贪婪的
        search_print(pattern1.search("abb")) # abb
        search_print(pattern2.search("abb")) # a


        pattern1 = re.compile("ab+")# 这里的+ 是贪婪的
        pattern2 = re.compile("ab+?")# 这里的+ 是非贪婪的
        search_print(pattern1.search("abb")) # abb
        search_print(pattern2.search("abb")) # ab

        pattern1 = re.compile("ab?")# 这里的? 是贪婪的
        pattern2 = re.compile("ab??")# 这里的? 是非贪婪的
        search_print(pattern1.search("abb")) # ab
        search_print(pattern2.search("abb")) # a

        
        pattern1 = re.compile("<.*>")# 这里的* 是贪婪的
        pattern2 = re.compile("<.*?>")# 这里的* 是非贪婪的
        search_print(pattern1.search("<a>hello</a>")) # <a>hello</a>
        search_print(pattern2.search("<a>hello</a>")) # <a>
    
    # 8 {m} 大括号:  对其之前的正则式指定匹配 m 个重复；少于 m 的话就会导致匹配失败。
    if 0 == 1:
        pattern = re.compile("ab{3}") # {m} 前面的正则表达式是 b 
        search_print(pattern.search("a")) #  None
        search_print(pattern.search("ab")) # None
        search_print(pattern.search("abbb")) # abbb
        search_print(pattern.search("abbc")) # None

    # 8 {m,n} 大括号: 对正则式进行 m 到 n 次匹配，在 m(含) 和 n(含) 之间取尽量多。贪婪
    if 0 == 1:
        pattern = re.compile("ab{1,5}") # {m,n} 前面的正则表达式是 b 
        search_print(pattern.search("a")) # None
        search_print(pattern.search("ab")) # ab
        search_print(pattern.search("abb")) # abb
        search_print(pattern.search("abbb")) # abbb
        search_print(pattern.search("abbbb")) # abbbb
        search_print(pattern.search("abbbbb")) # abbbbb
        search_print(pattern.search("abbbbc")) # abbbb

    # 9 {m,n}? 大括号: 对正则式进行 m 到 n 次匹配，在 m(含) 和 n(含) 之间取尽量少。非贪婪
    if 0 == 1:
        pattern = re.compile("ab{1,5}?") # {m,n} 前面的正则表达式是 b 
        search_print(pattern.search("a")) # None
        search_print(pattern.search("ab")) # ab
        search_print(pattern.search("abb")) # ab
        search_print(pattern.search("abbb")) # ab
        search_print(pattern.search("abbbb")) # ab
        search_print(pattern.search("abbbbb")) # ab
        search_print(pattern.search("abbbbc")) # ab

    # 10 \ 转义字符: 允许你匹配 '*', '?', 或者此类其他，或者表示一个特殊序列,特殊序列之后进行讨论
    if 0 == 1:
        pattern = re.compile(r"a\**") # * 前面的正则表达式是 \* ,注意要使用raw string，不然很麻烦
        search_print(pattern.search("a")) # a
        search_print(pattern.search("a*")) # a*
        search_print(pattern.search("a**")) # a**

    # 11 [] 中括号: 用于表示一个字符集合。
    """
    在集合中：
    1.字符可以单独列出，比如 [amk] 匹配 'a'， 'm'， 或者 'k'。
    2.可以表示字符范围，通过用 '-' 将两个字符连起来。比如 [a-z] 将匹配任何小写ASCII字符， [0-5][0-9] 将匹配从 00 到 59 的两位数字， [0-9A-Fa-f] 将匹配任何十六进制数位。 如果 - 进行了转义 （比如 [a\-z]）或者它的位置在首位或者末尾（如 [-a] 或 [a-]），它就只表示普通字符 '-'。
    3.特殊字符在集合中，失去它的特殊含义。比如 [(+*)] 只会匹配这几个文法字符 '(', '+', '*', or ')'。
    4.字符类如 \w 或者 \S (如下定义) 在集合内可以接受，它们可以匹配的字符由 ASCII 或者 LOCALE 模式决定。
    5.不在集合范围内的字符可以通过 取反 来进行匹配。如果集合首字符是 '^' ，所有 不 在集合内的字符将会被匹配，比如 [^5] 将匹配所有字符，除了 '5'， [^^] 将匹配所有字符，除了 '^'. ^ 如果不在集合首位，就没有特殊含义。
    6.在集合内要匹配一个字符 ']'，有两种方法，要么就在它之前加上反斜杠，要么就把它放到集合首位。比如， [()[\]{}] 和 []()[{}] 都可以匹配括号。
    7.Unicode Technical Standard #18 里的嵌套集合和集合操作支持可能在未来添加。这将会改变语法，所以为了帮助这个改变，一个 FutureWarning 将会在有多义的情况里被 raise，包含以下几种情况，集合由 '[' 开始，或者包含下列字符序列 '--', '&&', '~~', 和 '||'。为了避免警告，需要将它们用反斜杠转义。



    """
    if 0 == 1:
        # [()[\]{}] 可以匹配  '(' ')' '[' ']' '{' '}' 
        # []()[{}]  可以匹配  ']' '(' ')' '[' '{' '}' 
        pattern1 = re.compile(r"[()[\]{}]+") 
        pattern2 = re.compile(r"[]()[{}]+") 

        search_print(pattern1.search("()[]{}"))  # () [] {}
        search_print(pattern2.search("()[]{}")) # () [] {}


    # 12 | 管道符: 任意个正则表达式可以用 '|' 连接。
    # A|B: A 和 B 可以是任意正则表达式。创建新一个正则表达式，匹配 A 或者 B. 
    # 一旦 A 匹配成功， B 就不再进行匹配, 不贪婪
    if 0 == 1:
        pattern = re.compile(r"ab+|xy+")
        search_print(pattern.search("ab")) # ab
        search_print(pattern.search("xy")) # xy
        search_print(pattern.search("abxy")) # ab
        search_print(pattern.search("xyab")) # xy

    # 13 (...) 组合:  匹配括号内的任意正则表达式，并标识出组合的开始和结尾。匹配完成后，组合的内容可以被获取,并可以在之后用 \number 进行再次匹配，后面进行详细说明。
    if 0 == 1:
        pattern = re.compile(r"(ab+)")
        search_print(pattern.search("helloab")) # ab
        search_print(pattern.search("helloabab")) # ab 


        print("====>===>")
        pattern = re.compile(r"(ab+)\1")
        search_print(pattern.search("helloab")) # None
        search_print(pattern.search("helloabab")) # abab 

        print("====>===>")
        pattern = re.compile(r"(ab+)\1\1")
        search_print(pattern.search("helloab")) # None
        search_print(pattern.search("helloabab")) # None 
        search_print(pattern.search("helloababab")) # ababab

        if 0 == 1:
            # ==== r"(ab+)\1") 和 r"(ab+)(ab+)" 的区别 
            pattern = re.compile(r"(ab+)\1")
            ret = pattern.search("helloababb")
            if ret:
                print("====>===>")
                print ret.group() # abab
                print ret.group(0) # abab  # 0 就是默认的，entire match 

                print ret.group(1) #ab  # first group 
                # print ret.group(2) # 没有 second group  \1 代表的是ab+匹配出来的结果，仅仅是重复

            # ====
            pattern = re.compile(r"(ab+)(ab+)")
            ret = pattern.search("helloababb")
            if ret:
                print("====>===>")
                print ret.group() # ababb (3个b)
                print ret.group(0)# ababb # 0 就是默认的，entire match 

                print ret.group(1) # ab  # first group 
                print ret.group(2) # abb # second group
            
    # =======================================特殊序列========================================
    # 1 \number : 
    # 匹配数字代表的组合。每个括号是一个组合，组合从1开始编号。比如 (.+) \1 匹配 'the the' 或者 '55 55', 但不会匹配 'thethe' (注意组合后面的空格)。这个特殊序列只能用于匹配前面99个组合。
    # 例子见 上面 【13 组合】 内容

    # 2 \d : 匹配数字字符 digit
    # 3 \D : 匹配非数字字符
    if 0 == 1:
        pattern = re.compile(r"age=(\d+)$")
        ret = pattern.search("age=18")
        if ret:
            print ret.group(1)

    # 4 \w :匹配单词字符 word
    # 5 \W :匹配非单词字符
    if 0 == 1:
        pattern = re.compile(r"name=(\w+)$")
        ret = pattern.search("name=tom")
        if ret:
            print ret.group(1)

    # 6 \s :匹配空白字符 space
    # 7 \S :匹配非空白字符

