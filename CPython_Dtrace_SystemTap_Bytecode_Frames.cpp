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
 The following script uses the tapset above to provide a top-like view of all running CPython code, showing the top 20 most frequently-entered bytecode
 frames, each second, across the whole system:
*/ 

global fn_calls;

probe python.function.entry
{

    fn_calls[pid(), filename, funcname, lineno] += 1;

}

probe timer.ms(1000) {
    printf("\033[2J\033[1;1H") /* clear screen \*/

    printf("%6s %80s %6s %30s %6s\n",
           "PID", "FILENAME", "LINE", "FUNCTION", "CALLS")

    foreach ([pid, filename, funcname, lineno] in fn_calls- limit 20) {

        printf("%6d %80s %6d %30s %6d\n",
            pid, filename, lineno, funcname,
            fn_calls[pid, filename, funcname, lineno]);

    }

    delete fn_calls;

}
