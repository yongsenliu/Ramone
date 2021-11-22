/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Copyright (C) 2018 Konsulko Group
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.2

Item {
    id: valueSource
//    property bool mphDisplay: true
//    property real speedScaling: mphDisplay == true ? 0.621 : 1.0
    property real kph: 0
    property real rpm: rpmHezar/1000
    property real rpmHezar: 0
    property real fuel: 0

    property real temperature: 0
    property real oil_temp: 0
    Behavior on kph { NumberAnimation { duration: 500 } }
    Behavior on rpm { NumberAnimation { duration: 200 } }
    Behavior on temperature { NumberAnimation { duration: 1/*500*/ } }
    Behavior on fuel { NumberAnimation { duration: 1/*500*/ } }
    Behavior on oil_temp { NumberAnimation { duration: 1/*500*/ } }

//    Behavior on kph {
//        animation: du
//    }



//    property string txt: ""
    property string gear: "0"/* {
        var g;
        if (kph < 30) {
            return "1";
        }
        if (kph < 50) {
            return "2";
        }
        if (kph < 80) {
            return "3";
        }
        if (kph < 120) {
            return "4";
        }
        if (kph < 160) {
            return "5";
        }
    }*/
    property int pindle_int: 0
    property string prindle:  {
        var g;
        if (pindle_int == 0) {
            return "P";
        } else if (pindle_int == 1) {
            return "N";
        } else if (pindle_int == 2) {
            return "R";
        } else if (pindle_int == 3) {
            return "D";
        } else if (pindle_int == 4) {
            return "M";
        }
//        return "P";
    }

    property bool startDemo: {
        if (startUp) return true;
        else return false;
    }

    property bool left_blinker: false
    property bool engine_check: false
    property bool oil_check: false
    property bool abs: false
    property bool battery: false
    property bool seat_belt: false
    property bool doors_open: false
    property bool high_beam: false
    property bool hand_break: false
    property bool right_blinker: false
    property bool startUp: false
    property string txt: "."

    SequentialAnimation {
        running: flase
       /* running: startDemo
        PropertyAction {
            target: valueSource
            property: "engine_check"
            value: true
        }
        PauseAnimation {
            duration: 200
        }
        PropertyAction {
            target: valueSource
            property: "engine_check"
            value: false
        }
        PauseAnimation {
            duration: 200
        }
        PropertyAction {
            target: valueSource
            property: "engine_check"
            value: true
        }
        PauseAnimation {
            duration: 200
        }*/
//        PropertyAction {
//            target: valueSource
//            property: "engine_check"
//            value: false
//        }
//        PauseAnimation {
//            duration: 200
//        }
//        PropertyAction {
//            target: valueSource
//            property: "engine_check"
//            value: true
//        }
//        PauseAnimation {
//            duration: 200
//        }
//        PropertyAction {
//            target: valueSource
//            property: "engine_check"
//            value: false
//        }
//        PauseAnimation {
//            duration: 100
//        }
        NumberAnimation {
            target: valueSource
            property: "kph"
            easing.type: Easing.InOutQuad
            from: 0
            to: 250
            duration: 700
        }
//        PropertyAction {
//            target: valueSource
//            property: "oil_check"
//            value: true
//        }
//        PropertyAction {
//            target: valueSource
//            property: "high_beam"
//            value: true
//        }
//        PauseAnimation {
//            duration: 200
//        }
//        PropertyAction {
//            target: valueSource
//            property: "abs"
//            value: true
//        }
//        PropertyAction {
//            target: valueSource
//            property: "doors_open"
//            value: true
//        }
//        PauseAnimation {
//            duration: 200
//        }
//        PropertyAction {
//            target: valueSource
//            property: "battery"
//            value: true
//        }
//        PropertyAction {
//            target: valueSource
//            property: "seat_belt"
//            value: true
//        }
        PauseAnimation {
            duration: 300
        }
//        PropertyAction {
//            target: valueSource
//            property: "oil_check"
//            value: false
//        }
//        PropertyAction {
//            target: valueSource
//            property: "high_beam"
//            value: false
//        }
//        PauseAnimation {
//            duration: 100
//        }
//        PropertyAction {
//            target: valueSource
//            property: "abs"
//            value: false
//        }
//        PropertyAction {
//            target: valueSource
//            property: "doors_open"
//            value: false
//        }
//        PauseAnimation {
//            duration: 100
//        }
//        PropertyAction {
//            target: valueSource
//            property: "battery"
//            value: false
//        }
//        PropertyAction {
//            target: valueSource
//            property: "seat_belt"
//            value: false
//        }
//        PauseAnimation {
//            duration: 100
//        }
        NumberAnimation {
            target: valueSource
            property: "kph"
            easing.type: Easing.InOutSine
            from: 250
            to: 0
            duration: 700
        }


    }







/*
    SequentialAnimation {
        running: true
        loops: 1

        // We want a small pause at the beginning, but we only want it to happen once.
        PauseAnimation {
            duration: 1000
        }

        PropertyAction {
            target: valueSource
            property: "start"
            value: false
        }

        SequentialAnimation {
            loops: Animation.Infinite

            // Simulate startup with indicators blink
            PropertyAction {
                target: valueSource
                property: "startUp"
                value: true
            }
            PauseAnimation {
                duration: 1000
            }
            PropertyAction {
                target: valueSource
                property: "startUp"
                value: false
            }

            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 0
                    to: 30
                    duration: 3000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    from: 1
                    to: 6.1
                    duration: 3000
                }
            }
            ParallelAnimation {
                // We changed gears so we lost a bit of speed.
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 30
                    to: 26
                    duration: 600
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    from: 6
                    to: 2.4
                    duration: 600
                }
            }
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 60
                    duration: 3000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 5.6
                    duration: 3000
                }
            }
            ParallelAnimation {
                // We changed gears so we lost a bit of speed.
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 56
                    duration: 600
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 2.3
                    duration: 600
                }
            }
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 100
                    duration: 3000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 5.1
                    duration: 3000
                }
            }
            ParallelAnimation {
                // We changed gears so we lost a bit of speed.
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 96
                    duration: 600
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 2.2
                    duration: 600
                }
            }

            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 140
                    duration: 3000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 6.2
                    duration: 3000
                }
            }

            // Slow down a bit
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 115
                    duration: 6000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 5.5
                    duration: 6000
                }
            }

            // Turn signal on
            PropertyAction {
                target: valueSource
                property: "turnSignal"
                value: randomDirection()
            }

            // Cruise for a while
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 110
                    duration: 10000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 5.2
                    duration: 10000
                }
            }

            // Turn signal off
            PropertyAction {
                target: valueSource
                property: "turnSignal"
                value: -1
            }

            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 115
                    duration: 10000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 5.5
                    duration: 10000
                }
            }

            // Start downshifting.

            // Fifth to fourth gear.
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.Linear
                    to: 100
                    duration: 5000
                }

                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 3.1
                    duration: 5000
                }
            }

            // Fourth to third gear.
            NumberAnimation {
                target: valueSource
                property: "rpm"
                easing.type: Easing.InOutSine
                to: 5.5
                duration: 600
            }

            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 60
                    duration: 5000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 2.6
                    duration: 5000
                }
            }

            // Third to second gear.
            NumberAnimation {
                target: valueSource
                property: "rpm"
                easing.type: Easing.InOutSine
                to: 6.3
                duration: 600
            }

            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 30
                    duration: 5000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 2.6
                    duration: 5000
                }
            }

            NumberAnimation {
                target: valueSource
                property: "rpm"
                easing.type: Easing.InOutSine
                to: 6.5
                duration: 600
            }

            // Second to first gear.
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 0
                    duration: 5000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutSine
                    to: 1
                    duration: 4500
                }
            }

            PauseAnimation {
                duration: 5000
            }
        }
    }
*/
}
