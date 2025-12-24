## Kprobes, Jprobes, Return Probes

Kprobes enables you to dynamically break into any kernel routine and collect debugging and performance information non-disruptively. 

You can trap at almost any kernel code address(*), specifying a handler routine to be invoked when the breakpoint is hit.

 
	A kprobe can be inserted on virtually any instruction in the kernel.
	A jprobe is inserted at the entry to a kernel function, and provides convenient access to the function's arguments.  
	A return probe fires when a specified function returns.
