
## Rest Programming Language

*Syntax Example:*
```

def range(start: int, end: int; step: int = 1): array[int]
    while start < end
        yield start
        start += step
    end
end

def main(args: array[string])
    # prints sum of 1 to 500
    var total = 0
    for i in range(1, 500)
        total += i
    end
    print(total)
end

```
