Massive Downloader
====================

Intro
-----
Download many files in parallel rather than single-download

Supported Platforms
--------------------
Basically system with "wget" will work like a charm, such as
- macOS<br>
  - wget needs to be installed from homebrew
- Linux
- Windows with wget<br>
  - It may works, but cannot guarantee.
  - Possibly wget should be on PATH

Description-KO/KR
------------
이 프로젝트는 몇십에서, 몇백, 혹은 몇 만가지의 파일을 다운 받을 때 "과연 더 빠르게 다운 받을 수 없을까?" 라는 생각을 기반으로 만들었습니다. <br>
간단히, 이 프로그램은 CPU의 Thread자원을 "모두" 사용해서 후술할 URL파일을 파싱하고, 다운로드 합니다.<br>
![](https://i.imgur.com/4BqfS9B.png)
위 사진은 CPU 스레드(논리 포함)가 총 4개일 때 프로그램이 작동하는 것을 도식화 한 것입니다.<br>
스레드는 실행 시간 시점에 결정이 되며, 각 스레드 마다 작업 큐를 가지고 있습니다. 즉, Parse file 부분[여기까지는 Single-Thread]에서는 각 스레드 큐에 작업을 push(Queue) 해주며, 이 작업이 완료 된 뒤로는 스레드 수 만큼 fork를 진행하게 됩니다. 위 그림 예제라면 총 4개의 프로세스가 fork 됩니다.

How to use
------------
```
./app.out "txt_file_path" "output_folder_path"
```
where
|Parameter|Desc.|Example|
|---|---|---|
|txt_file_path|The file to parse.|/Users/kangdroid/Desktop/test.txt|
|output_folder_path|Output folder|/Users/kangdroid/Desktop/output/|

For more about txt_file, please look at section "About text file"

About Text File
----------------
Basically in this project, program will parse a text file contains target url and file name. For example,<br>
Assuming image name is "2.png" and its url is "http://somewhaturl.kangdroid.com/something.png", the text file format would be
```
2.png	http://somewhaturl.kangdroid.com/something.png
```
As you can see, the file name is on first, and url came second. Between Name and URL, we have "Tab" indentation(NOT 4-space), which will be specifier when parsing. <br>
After parsing text file, program will "wget" its url and save with specified name in parallel.

Actual speed
-------------
With MacBook Pro 2019 16" with i9-9880H / 16GB / 1TB SSD, single-downloading of 600 image took about 1m 40seconds, while this program downloads 600 image in 5~6 seconds.