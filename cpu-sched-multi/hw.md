RT - Runtime
WSS - Working-set space -> Cache space needed to work effectively
-> Not effective, then running cold, 1 tick of its runtime subtracted per tick of clock
-> Effective, then warm, will run more quickly depending on value of the -r flag (2x default)

-> Note all takes time for cache to warm up, this value based on value of -w flag (10 time units default)
-> Note that while warming up, process is still running
1. 1 Job: RT: 30, WSS: 200
    Command: python3 multi.py -n 1 -L a:30:200
    How long to complete?
    30s right since its just 1 job? -> Yep! Also b/c running cold

2. python3 multi.py -n 1 -L a:30:200 -M 300
    How fast job runs once it fits in the cache?
    Timeline
    1   2   3                           w
    29  28  27  26                      20  18  16  14  12  10  8   6   4   2   0
    1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20
    Warmed up w/ effective rate @ 2x, so 2 runtime subtracted per tick of clock
    So 20s taken!
    While its warming up, the job is still running cold, when it finally warms, then it works @ effective rate
3. 
4. As you increase the -w time, it will take more time to warm up, meaning more time before job runs effectively!
5. Command: python3 multi.py -n 2 -q 20, -L a:100:100,b:100:50,c:100:50
    How long given RR scheduler? w/ Q = 20
    0 a 99 cache[ ]             b 99 cache[]
    1 a 98 cache[ ]             b 98 cache[]
    9 a 90 cache[w ]            b 90 cache[ w ]
    10 a 88 cache[w ]           b 88 cache[ w ]
    19 a 70                     b 70 cache[ w ]
    20 c 99 cache[w  ]          a 69 cache[ w ]
    21 c 98 cache[w  ]          a 68 cache[ w ]
    29 c 90 cache[  w]          a 60 cache[w  ]
    39 c 70 cache[  w]          a 40 cache[w  ]
    40 b 69 cache[  w]          c 69 cache[w  ]
    49 b 60 cache[ ww]          c 60 cache[  w]
    59 b 40 cache[ ww]          c 40 cache[  w]
    60 a 39 cache[ ww]          b 39 cache[  w]
    69 a 30 cache[w  ]          b 30 cache[ ww]
    79 a 10 cache[w  ]          b 10 cache[ ww]
    80 c 39 cache[w  ]          a 10 cache[ ww]
    89 c 30 cache[  w]          a 0  cache[w  ]
    90 c 28 cache[  w]          b 10 cache[w  ]
    ... 104s

6. In 5, Cache affinity was not utilized, you can see how cache affinity mightve sped things up! Best would be to put b & c on 1 cpu w/ a on another. Since b & c can effectively share the cache space (100).

7. Intersting aspect -> opportunity for better-than-expected speed up of jobs when using multiple CPUs (and their caches) when compared to singlue processor...
    When you run N CPUs, sometimes can speed up more than factor of N -> super-linear speedup
    Command: python3 multi.py -n x -L a:100:100,b:100:100,c:100:100 -M 50
    ... where x is N CPU
    1 -> 300
    2 -> 150 ~2x
    3 -> 100 
    4 -> 100 ...

8. adding the -p flag start the per-cpu scheduling queues, when used makes it so each CPU has queue of jobs. This speeds up performance... but note the value of the -P value dictates
python3 multi.py -n 2 -p -P 3 -L a:100:100,b:100:50,c:100:50 -M 50 -c
    Playing around with it, I noticed that the P-values had peaks & valleys from finish time. Meaning that something might run slower at the edge values than the ones in between
    There were several "pockets" of numbers that did this
