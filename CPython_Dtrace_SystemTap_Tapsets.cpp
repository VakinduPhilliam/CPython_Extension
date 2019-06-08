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
 SystemTap Tapsets
 The higher-level way to use the SystemTap integration is to use a “tapset”: SystemTap’s equivalent of a library, which hides some of the lower-level
 details of the static markers.
 Here is a tapset file, based on a non-shared build of CPython:
*/ 

/*
   Provide a higher-level wrapping around the function__entry and
   function__return markers:
 \*/
probe python.function.entry = process("python").mark("function__entry")
{
    filename = user_string($arg1);
    funcname = user_string($arg2);
    lineno = $arg3;
    frameptr = $arg4
}
probe python.function.return = process("python").mark("function__return")
{
    filename = user_string($arg1);
    funcname = user_string($arg2);
    lineno = $arg3;
    frameptr = $arg4
}
