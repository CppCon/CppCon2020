#include "HelloApprovals.h"

std::string HelloApprovals::helloApprovals()
{
    return "Hello Approvals";
}

std::string
HelloApprovals::helloPoetry( const std::string& /*language*/ )
{
    // From https://stackoverflow.com/a/5460235/104370
    return R"V0G0N(
             O freddled gruntbuggly thy micturations are to me
                 As plured gabbleblochits on a lurgid bee.
              Groop, I implore thee my foonting turlingdromes.
           And hooptiously drangle me with crinkly bindlewurdles,
Or I will rend thee in the gobberwarts with my blurlecruncheon, see if I don't.

                (by Prostetnic Vogon Jeltz; see p. 56/57)
)V0G0N";
}
