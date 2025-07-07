#include "id.h"

namespace ID
{
    int s_id = 0;

    int genId()
    {
        return s_id++;
    }
}