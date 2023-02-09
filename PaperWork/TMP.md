
### Q1-c

$Q: $
$ \log_\phi(\sqrt{5}(n+2)) - 2 \in O(\log_2(n)) $
$ \text{where} \ \phi \text{ is the golden ratio.} $

$ \text{Proof: }$



$\text{[WA] Proof: }$
$ \text{Define: } $

- $ minsize(h) \text{ as the smallest number } n \text{ that a AVL tree of height } h \text{ can have;} $
- $ fib(h) \text{ as the } h^{th} \text{ Fibonacci number (starting from 1).} $

$ \text{By definition of AVL tree, } $
$$ minsize(h) = minsize(h-1) + minsize(h-2) + 1 $$

$ \text{Where } $
$$ minsize(h-1) + minsize(h-2) \text{ follows the Fibonacci sequence} $$
$ \text{Then is follows that: } $
$$ minsize(0) = 0, minsize(1) = 1 $$
$$ \Rightarrow minsize(h - 1) + minsize(h - 2) + 1 = fib(h + 1) + fib(h) - 1 $$
$$ \Rightarrow minsize(h) = fib(h + 2) - 1 $$

$ \text{By definition of Fibonacci sequence, } $
$$ fib(h) = \frac{\phi^h - \phi^{-h}}{\sqrt{5}} $$
$$ \text{where } \phi = \frac{1+\sqrt{5}}{2} \text{and } \psi = \frac{1-\sqrt{5}}{2} $$

$ \text{Note that } $
$$ \frac{1}{\sqrt{5}} \cdot \psi = \frac{1}{\sqrt{5}} \cdot \frac{1-\sqrt{5}}{2} = \frac{1-\sqrt{5}}{2\sqrt{5}} \leq 0 < 1 $$
$$ \Rightarrow minsize(h) = \frac{1}{\sqrt{5}} \cdot \phi^{h+2} - \frac{1}{\sqrt{5}} \cdot \psi^{h+1} - 1 > \frac{1}{\sqrt{5}} \cdot \phi^{h+2} - 1 - 1 $$
$ \text{Let number of nodes in an AVL tree of height } h \text{ be } n \text{, then: } $
$$ n = minsize(h) > \frac{1}{\sqrt{5}} \cdot \phi^{h+2} - 1 - 1 = \frac{1}{\sqrt{5}} \cdot \phi^{h+2} - 2 $$
$$ \phi^{h+2} < \sqrt{5} \cdot (n+2) $$
$$ h+2 < \log_\phi(\sqrt{5}(n+2))\ \ (\text{since }\phi > 1) $$
$$ h < \log_\phi(\sqrt{5}(n+2)) - 2 $$