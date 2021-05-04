正则表达式，又称规则表达式。（英语：Regular Expression，在代码中常简写为regex、regexp或RE），计算机科学的一个概念。


[参考文档](https://docs.python.org/zh-cn/3/library/re.html)

[参考文档2](http://robot.czxy.com/docs/spider/01_regex/)



三个常见的作用：

    1. 验证: 对数据进行有效性验证

    2. 替换: 实现按照某种规则替换文本

    3. 提取: 从一个字符串中提取出其中子字符串

正则表达式的构成:

    1. 普通字符，例如 1-9,a-z,A-Z  它们就匹配自身

    2. 特殊字符, 例如 .^$|()\*+?{}  特殊字符既可以表示它的普通含义， 也可以影响它旁边的正则表达式的解释。

