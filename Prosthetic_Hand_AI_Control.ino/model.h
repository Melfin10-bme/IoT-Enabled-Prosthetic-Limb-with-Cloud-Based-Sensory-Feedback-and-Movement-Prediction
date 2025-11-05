#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class ProstheticHandModel {
                public:
                    /**
                    * Predict class for features vector
                    */
                    float predict(float *x) {
                        float y_pred = 0;
                        // tree #1
                        if (x[0] <= 2507.0) {
                            if (x[0] <= 510.0) {
                                if (x[1] <= 382.0) {
                                    if (x[0] <= 342.0) {
                                        y_pred += 183.0;
                                    }

                                    else {
                                        if (x[1] <= 338.5) {
                                            y_pred += 187.0;
                                        }

                                        else {
                                            y_pred += 188.0;
                                        }
                                    }
                                }

                                else {
                                    if (x[0] <= 432.5) {
                                        y_pred += 196.0;
                                    }

                                    else {
                                        y_pred += 200.0;
                                    }
                                }
                            }

                            else {
                                if (x[4] <= -4.409999847412109) {
                                    y_pred += 209.0;
                                }

                                else {
                                    y_pred += 223.0;
                                }
                            }
                        }

                        else {
                            y_pred += 600.0;
                        }

                        // tree #2
                        if (x[0] <= 2507.0) {
                            if (x[0] <= 714.0) {
                                if (x[0] <= 365.5) {
                                    if (x[1] <= 332.5) {
                                        if (x[0] <= 315.5) {
                                            y_pred += 183.0;
                                        }

                                        else {
                                            y_pred += 185.0;
                                        }
                                    }

                                    else {
                                        y_pred += 188.0;
                                    }
                                }

                                else {
                                    if (x[0] <= 498.5) {
                                        if (x[3] <= 8.570000171661377) {
                                            y_pred += 200.0;
                                        }

                                        else {
                                            y_pred += 196.0;
                                        }
                                    }

                                    else {
                                        y_pred += 209.0;
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 912.0) {
                                    y_pred += 240.0;
                                }

                                else {
                                    y_pred += 223.0;
                                }
                            }
                        }

                        else {
                            if (x[1] <= 2341.0) {
                                y_pred += 407.0;
                            }

                            else {
                                y_pred += 600.0;
                            }
                        }

                        // tree #3
                        if (x[0] <= 2507.0) {
                            if (x[0] <= 510.0) {
                                if (x[1] <= 374.5) {
                                    if (x[4] <= -4.409999847412109) {
                                        y_pred += 183.0;
                                    }

                                    else {
                                        y_pred += 187.0;
                                    }
                                }

                                else {
                                    if (x[1] <= 461.5) {
                                        y_pred += 200.0;
                                    }

                                    else {
                                        y_pred += 196.0;
                                    }
                                }
                            }

                            else {
                                if (x[2] <= -0.255000002682209) {
                                    if (x[2] <= -0.3100000023841858) {
                                        y_pred += 209.0;
                                    }

                                    else {
                                        y_pred += 223.0;
                                    }
                                }

                                else {
                                    y_pred += 240.0;
                                }
                            }
                        }

                        else {
                            y_pred += 600.0;
                        }

                        // tree #4
                        if (x[0] <= 2500.0) {
                            if (x[0] <= 701.0) {
                                if (x[1] <= 382.0) {
                                    if (x[0] <= 342.0) {
                                        if (x[1] <= 311.0) {
                                            y_pred += 183.0;
                                        }

                                        else {
                                            y_pred += 185.0;
                                        }
                                    }

                                    else {
                                        if (x[2] <= -0.19999999552965164) {
                                            y_pred += 187.0;
                                        }

                                        else {
                                            y_pred += 188.0;
                                        }
                                    }
                                }

                                else {
                                    y_pred += 200.0;
                                }
                            }

                            else {
                                y_pred += 240.0;
                            }
                        }

                        else {
                            if (x[1] <= 2341.0) {
                                y_pred += 407.0;
                            }

                            else {
                                y_pred += 600.0;
                            }
                        }

                        // tree #5
                        if (x[0] <= 2507.0) {
                            if (x[3] <= 8.450000286102295) {
                                if (x[1] <= 589.0) {
                                    y_pred += 223.0;
                                }

                                else {
                                    y_pred += 240.0;
                                }
                            }

                            else {
                                if (x[0] <= 365.5) {
                                    if (x[0] <= 346.0) {
                                        if (x[4] <= -4.369999885559082) {
                                            y_pred += 183.0;
                                        }

                                        else {
                                            y_pred += 185.0;
                                        }
                                    }

                                    else {
                                        y_pred += 188.0;
                                    }
                                }

                                else {
                                    if (x[2] <= -0.3100000023841858) {
                                        y_pred += 209.0;
                                    }

                                    else {
                                        if (x[2] <= -0.255000002682209) {
                                            y_pred += 196.0;
                                        }

                                        else {
                                            y_pred += 200.0;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 2341.0) {
                                y_pred += 407.0;
                            }

                            else {
                                y_pred += 600.0;
                            }
                        }

                        // tree #6
                        if (x[0] <= 2507.0) {
                            if (x[3] <= 8.450000286102295) {
                                if (x[0] <= 912.0) {
                                    y_pred += 240.0;
                                }

                                else {
                                    y_pred += 223.0;
                                }
                            }

                            else {
                                if (x[1] <= 388.0) {
                                    if (x[0] <= 343.0) {
                                        if (x[2] <= -0.23499999940395355) {
                                            y_pred += 183.0;
                                        }

                                        else {
                                            y_pred += 184.0;
                                        }
                                    }

                                    else {
                                        y_pred += 187.0;
                                    }
                                }

                                else {
                                    if (x[2] <= -0.255000002682209) {
                                        y_pred += 196.0;
                                    }

                                    else {
                                        y_pred += 200.0;
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 2341.0) {
                                y_pred += 407.0;
                            }

                            else {
                                y_pred += 600.0;
                            }
                        }

                        // tree #7
                        if (x[0] <= 2500.0) {
                            if (x[0] <= 714.0) {
                                if (x[1] <= 412.0) {
                                    if (x[1] <= 324.5) {
                                        if (x[0] <= 330.0) {
                                            y_pred += 183.0;
                                        }

                                        else {
                                            y_pred += 184.0;
                                        }
                                    }

                                    else {
                                        y_pred += 188.0;
                                    }
                                }

                                else {
                                    if (x[3] <= 8.570000171661377) {
                                        y_pred += 209.0;
                                    }

                                    else {
                                        y_pred += 196.0;
                                    }
                                }
                            }

                            else {
                                y_pred += 240.0;
                            }
                        }

                        else {
                            if (x[1] <= 2341.0) {
                                y_pred += 407.0;
                            }

                            else {
                                y_pred += 600.0;
                            }
                        }

                        // tree #8
                        if (x[0] <= 2500.0) {
                            if (x[0] <= 714.0) {
                                if (x[0] <= 414.5) {
                                    if (x[1] <= 311.0) {
                                        y_pred += 183.0;
                                    }

                                    else {
                                        if (x[1] <= 325.0) {
                                            y_pred += 185.0;
                                        }

                                        else {
                                            y_pred += 187.0;
                                        }
                                    }
                                }

                                else {
                                    if (x[4] <= -4.389999866485596) {
                                        y_pred += 209.0;
                                    }

                                    else {
                                        y_pred += 200.0;
                                    }
                                }
                            }

                            else {
                                y_pred += 240.0;
                            }
                        }

                        else {
                            if (x[1] <= 2341.0) {
                                y_pred += 407.0;
                            }

                            else {
                                y_pred += 600.0;
                            }
                        }

                        // tree #9
                        if (x[0] <= 2507.0) {
                            if (x[0] <= 701.0) {
                                if (x[1] <= 382.0) {
                                    if (x[0] <= 342.0) {
                                        if (x[1] <= 304.5) {
                                            y_pred += 183.0;
                                        }

                                        else {
                                            y_pred += 185.0;
                                        }
                                    }

                                    else {
                                        if (x[4] <= -4.409999847412109) {
                                            y_pred += 188.0;
                                        }

                                        else {
                                            y_pred += 187.0;
                                        }
                                    }
                                }

                                else {
                                    if (x[1] <= 461.5) {
                                        y_pred += 200.0;
                                    }

                                    else {
                                        y_pred += 196.0;
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 912.0) {
                                    y_pred += 240.0;
                                }

                                else {
                                    y_pred += 223.0;
                                }
                            }
                        }

                        else {
                            if (x[4] <= -4.450000047683716) {
                                y_pred += 407.0;
                            }

                            else {
                                y_pred += 600.0;
                            }
                        }

                        // tree #10
                        if (x[1] <= 2326.0) {
                            if (x[0] <= 365.5) {
                                if (x[1] <= 332.5) {
                                    if (x[4] <= -4.369999885559082) {
                                        y_pred += 183.0;
                                    }

                                    else {
                                        if (x[2] <= -0.2150000035762787) {
                                            y_pred += 185.0;
                                        }

                                        else {
                                            y_pred += 184.0;
                                        }
                                    }
                                }

                                else {
                                    y_pred += 188.0;
                                }
                            }

                            else {
                                if (x[0] <= 510.0) {
                                    if (x[0] <= 421.0) {
                                        y_pred += 196.0;
                                    }

                                    else {
                                        y_pred += 200.0;
                                    }
                                }

                                else {
                                    if (x[1] <= 492.0) {
                                        y_pred += 223.0;
                                    }

                                    else {
                                        y_pred += 209.0;
                                    }
                                }
                            }
                        }

                        else {
                            y_pred += 600.0;
                        }

                        return y_pred / 10;
                    }

                protected:
                };
            }
        }
    }