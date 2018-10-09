The purpose of this page is to outline notable components of existing BSQ solutions/

When times are on the order of tens of milliseconds, the comparison is lost in the noise.

| repo id | authorfile | notable component |  URL | 
|----|------------|------------------|------------|
| 0 |mvann:rariosa- | stores field as bits in unsigned long |  https://github.com/MrRobb/42_piscine/ |
| 1 |pebraun:fwuensch| -- | https://github.com/fwuensche/42-piscine-c/ |
| 2 |pcrosnie:cmutti| consistent 0.007s average | https://github.com/Tolo789/BSQ |
| 3 |	   |           |                  | https://github.com/vmarchaud/42-piscine/|
| 4 |      |           |                   | https://github.com/hopeczuba/bsq |
| 5 |      |           |                   |  https://github.com/SuperSpyTX/42-Piscine/ |
| 9 |jaleman:jguzman-|           |   0.005s                | https://github.com/jraleman/42_Piscine-C |


# Memory use
I'm using RSS/filesize as the metric for comparison.  This shows how memory consumption scales to large datasets.
| repo id | lowest RSS / filesize |
|---------|-----------------------|
|  0 |1.41 |
| 2 | 2.17 |
| 9 | 2.43 |
| 14 | 2.43 |

# Speed
| repo id | max solve time (s) (100x50000) |
|---------|-----------------------|
|  2 | 0.102 |
| 14 | 0.184 |
| 0 | 0.292 |

# We can malloc absurd amounts of data, but it only shows up in `top/htop` when it is used.
e.g.
```

#include <stdlib.h>

#define ONE_THOUSAND 1000
#define TEN_M (10 * ONE_THOUSAND * ONE_THOUSAND)

int main()
{
    char *stuff;

    stuff = malloc(TEN_M);
    while (1)
    {
        ;
    }
}
```
has a RSS < 1 MiB (800 KiB reported by `htop`, 304 K reported by `top`)


but this uses the full 10M:
```
int main()
{
    char *stuff;

    stuff = malloc(TEN_M);
    for (int i = 0; i < TEN_M; i++)
    {
        stuff[i] = 0;
    }
    while (1)
    {
        ;
    }
}
```

and this uses only 5M!

```
int main()
{
    char *stuff;

    stuff = malloc(TEN_M);
    for (int i = 0; i < TEN_M / 2; i++)
    {
        stuff[i] = 0;
    }
    while (1)
    {
        ;
    }
}
```