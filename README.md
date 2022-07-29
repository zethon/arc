# Another Reddit Client (`arc`)

[![macos](https://github.com/zethon/arc/actions/workflows/macos.yml/badge.svg)](https://github.com/zethon/arc/actions/workflows/macos.yml) [![ubuntu](https://github.com/zethon/arc/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/zethon/arc/actions/workflows/ubuntu.yml) [![windows](https://github.com/zethon/arc/actions/workflows/windows.yml/badge.svg)](https://github.com/zethon/arc/actions/workflows/windows.yml)
## Introduction


🔎 &nbsp; While searching for console clients for Reddit, I discovered that of the few tools that existed, they were all written in either Python or Javascript. This required various tools to download and run, adding additional requirements and work to get any of them to work. And even once all the requirements were installed, some of them still didn't work!

`arcc` is console client for Reddit written in C++. What does this mean?

* 👎 **NO** Javascript, Python, ScriptLanguageOfTheDay modules to install!
* 👎 **NO** `npm`, `brew`, `someotherthirdpartytool` to deal with!
* 👎 **NO** BS!

```
const dedupe = (array) => [...new Set(array)];
```

<!-- footnotes -->
[travis-img]: https://travis-ci.org/zethon/arcc.svg?branch=master
[travis]: https://travis-ci.org/zethon/arcc

[appveyor-img]: https://ci.appveyor.com/api/projects/status/goko4jxjkxhmvchq?svg=true
[appveyor]: https://ci.appveyor.com/project/zethon/arcc
