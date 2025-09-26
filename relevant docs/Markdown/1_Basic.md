# 1: Basic formats  

Basic Formats. 

## 1.1  Strengthen

use __*__ or **_** to create italic,bold,bold italic text
Example:  

Hello world!
_Hello world!_
__Hello world!__
___Hello world!___

## 1.2  Subtitle

use __#__ to create subtitle, number of __#__ controls size
Example:  

# Test 1
## Test 2
### Test 3

## 1.3  Split Line

use __---__; ___***___; ___ to create split line
Example:

---

## 1.4  List

use __-__ to create list
Example:  

- point 1  
- point 2
- point 3

1. point 1  
2. point 2  
3. point 3

## 1.5  Quote

use tab to create layer, __>__ to create a quote
Example:

    text_hilighted(tab)

> text_hilighted(>)

## 1.6  Code

use __\`__ to mark text as code
Example:  

`These are codes.`

use __\`\`\`__+__\`\`\`__ to create a code block, you can also specify the language to use


``` C
int main()
{
    printf(Hello,markdown!\n);
}
```

## 1.7  Weblink

use [LinkTitle](https://markdown.com.cn/basic-syntax/links.html "Comments") to create a weblink  

can create differently looked link:  
*[Link1](https://markdown.com.cn/basic-syntax/links.html "Comments")*  
**[Link2](https://markdown.com.cn/basic-syntax/links.html "Comments")**  
***[Link3](https://markdown.com.cn/basic-syntax/links.html "Comments")***  

use __%20__ to replace space in url