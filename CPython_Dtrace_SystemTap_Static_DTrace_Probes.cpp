/* CPython Dtrace SystemTap
  Instrumenting CPython with DTrace and SystemTap.
  DTrace and SystemTap are monitoring tools, each providing a way to inspect what the processes on a computer system are doing.
  They both use domain-specific languages allowing a user to write scripts which:
 
  > filter which processes are to be observed
  > gather data from the processes of interest
  > generate reports on the data
 
  CPython can be built with embedded “markers”, also known as “probes”, that can be observed by a DTrace or SystemTap script, making it easier to monitor
  what the CPython processes on a system are doing.
 
  CPython implementation detail: DTrace markers are implementation details of the CPython interpreter. 
  No guarantees are made about probe compatibility between versions of CPython. 
  DTrace scripts can stop working or work incorrectly without warning when changing CPython versions.
*/

/* 
 Static DTrace probes
 The following example DTrace script can be used to show the call/return hierarchy of a Python script, only tracing within the invocation of a function
 called “start”. 
 In other words, import-time function invocations are not going to be listed:
*/ 

self int indent;

python$target:::function-entry
/copyinstr(arg1) == "start"/
{
        self->trace = 1;
}

python$target:::function-entry
/self->trace/
{
        printf("%d\t%*s:", timestamp, 15, probename);
        printf("%*s", self->indent, "");
        printf("%s:%s:%d\n", basename(copyinstr(arg0)), copyinstr(arg1), arg2);
        self->indent++;
}

python$target:::function-return
/self->trace/
{
        self->indent--;
        printf("%d\t%*s:", timestamp, 15, probename);
        printf("%*s", self->indent, "");
        printf("%s:%s:%d\n", basename(copyinstr(arg0)), copyinstr(arg1), arg2);
}

python$target:::function-return
/copyinstr(arg1) == "start"/
{
        self->trace = 0;
}
