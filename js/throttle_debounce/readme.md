

## 防抖 和 节流 有什么区别 ?

节流 throttle:

避免调用过于频繁, 而限制调用的频率,

eg: at 12:00 调用了 api, api 的节流策略是 15min 之内只能调用一次, 则在 12:00 ~ 12:14 这段时间内都不能再次调用 api,  在 12:15 ~ ... 才能再次进行调用

防抖 debounce:

在满足某些条件的情况下, 才进行调用

eg: 用户 resize window, 在用户不断触发 resize 操作的时候, 不能每次都调用函数, 而需要等待用户停止 resize 操作一段时间以后, 才进行函数调用

## debounce 的实现:

```js
// debounce

const debounce = (func, delay) => {
  let inDebounce = null;
  return function() {
    const context = this
    const args = arguments
    clearTimeout(inDebounce)
    inDebounce = setTimeout(() => func.apply(context, args), delay)
  }
}

const btn = document.getElementById('btn');

btn.addEventListener('click', debounce(function() {
  console.info('Hey! It is', new Date().toUTCString());
}, 3000));
```


## 经典的 throttle 的实现:

```js
const throttle = (func, limit) => {
  let inThrottle = false;
  return function() {
    const args = arguments
    const context = this
    if (!inThrottle) {
      func.apply(context, args)
      inThrottle = true
      setTimeout(() => inThrottle = false, limit)
    }
  }
}

const btn = document.getElementById('btn');

btn.addEventListener('click', throttle(function() {
  console.info('Hey! It is', new Date().toUTCString());
}, 1000));
```

## 上面的 throttle 实现存在什么问题 ? 如何解决 ?

在 throttle 的间隔范围内, 上面的实现会忽略最后一次的函数调用, 但是我们在鼠标移动或者 resize 的操作中, 是需要将最后一次的调用进行执行的, 而不能忽略

解决方法: 当最后一次调用被触发, 并且经过了 *limit 的剩余时间*, 会对函数进行调用.

也就是: (假如下面的是时间, 假设 limit 是 10)

1(发生点击, 产生调用) 2 3 4 5(有点击, 无调用) 6 7 8 9 10(无点击, 有调用) 11 12 13(有点击, 无调用, 在 20 有调用) 14 ...

```js
const throttle = (func, limit) => {
  let lastFunc
  let lastRan
  return function() {
    const context = this
    const args = arguments
    if (!lastRan) {
      // 记录第一次运行的时间
      func.apply(context, args)
      lastRan = Date.now()
    } else {
      clearTimeout(lastFunc)
      lastFunc = setTimeout(function() {
        if ((Date.now() - lastRan) >= limit) {
          func.apply(context, args)
          lastRan = Date.now()
        }
      }, limit - (Date.now() - lastRan))
    }
  }
}

const btn = document.getElementById('btn');

btn.addEventListener('click', throttle(function() {
  console.info('发生点击 !');
}, 10000));
```

以上实现有点类似于 debounce, 只是传入的 delay 不同,


