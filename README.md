tekken-helper
========
> 2012-04-18 ~ 2012-04-19

프로그램을 켠 채로 <kbd>E</kbd>나 <kbd>Q</kbd>를 누르면 자동으로 `d(중립)sdi`,
`a(중립)sai` 키이벤트가 발생합니다. 간단한 코딩만 할 줄 알면 당신도 국민이 될 수
있습니다!

고등학생시절 연습용으로 짠 프로그램입니다.

![Kazuya hitting Paul with EWGF](https://i.hyeon.me/tekken-helper/image.jpg)

```bash
zig build-exe main.zig -O ReleaseSmall -fstrip -fsingle-threaded -target x86_64-windows
./main.exe
```

&nbsp;

--------
*tekken-helper* is primarily distributed under the terms of both the [MIT
license] and the [Apache License (Version 2.0)]. See [COPYRIGHT] for details.

[MIT license]: LICENSE-MIT
[Apache License (Version 2.0)]: LICENSE-APACHE
[COPYRIGHT]: COPYRIGHT
