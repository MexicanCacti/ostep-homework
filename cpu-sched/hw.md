Response T`ime - Time job spends waiting before first running
Turnaround Time - Time took to complete job since arrival
Wait Time - Time spent ready but not running

  Job 0 ( length = 2 )
  Job 1 ( length = 5 )
  Job 2 ( length = 8 )
  FIFO

  Turnaround Time
0 - 2
1 - 7
2 - 15

  Response Time
0 - 0
1 - 2
2 - 7

  Wait Time
0 - 0
1 - 2
2 - 7

  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )
  FIFO

  Turnaround Time
0 - 100
1 - 300
2 - 600

  Response Time
0 - 0
1 - 100
2 - 300

  Wait Time
0 - 0
1 - 100
2 - 300

  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )
  SJF

  Turnaround Time
0 - 100
1 - 300
2 - 600

  Response Time
0 - 0
1 - 100
2 - 300

  Wait Time
0 - 0
1 - 100
2 - 300


  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )
  RR, Q: 1

  Turnaround Time
0 - 298
1 - 499
2 - 600

  Response Time
0 - 0
1 - 1
2 - 2

  Wait Time
0 - 198
1 - 299
2 - 300

4. For what types of workloads does SJF do same turnaround as FIFO?
    - When the jobs that come in FIFO are already ordered from shortest to longest

5. For what type of workloads & quantum  length does SJF deliver same response time as RR
    - When the jobs come in shortest to longest & the quantum is large enough such that no job is switched out before completion

6. What happens to response times as job lengths increase in SJF?
    - As job lengths increase, response times increase for the later jobs as they have to wait for these longer jobs to increase.

7. What happens to response time with RR as quantum lengths increase?
    - As quantum lengths increase, the response time increases as well! It morphs more into a FIFO as the quantum increases as there are no context switching happening mid-jobs.
    Given N jobs, the worst case response time is going to be the quantum that ensures that no job is context switched mid job. This quantum is going to be the maximum job length excluding the last job being considered.
    Worst-Response-Time = SUM(Length of every job except last) Using Worst-Quantum
    Worst-Quantum = MAX(Length of every job except last)