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
 python.function.return(str filename, str funcname, int lineno, frameptr) 
 This probe point is the converse of python.function.return(), and indicates that execution of a Python function has ended (either via return, or via an
 exception). 
 It is only triggered for pure-Python (bytecode) functions.
*/ 

/*
 Examples:
 This SystemTap script uses the tapset above to more cleanly implement the example given above of tracing the Python function-call hierarchy, without 
 needing to directly name the static markers.
*/ 

probe python.function.entry
{

  printf("%s => %s in %s:%d\n",
         thread_indent(1), funcname, filename, lineno);

}

probe python.function.return
{

  printf("%s <= %s in %s:%d\n",
         thread_indent(-1), funcname, filename, lineno);

}
