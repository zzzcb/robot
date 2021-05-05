//
// Created by zcb on 4/17/21.

#include <iostream>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames_io.hpp>

using namespace std;
using namespace KDL;

/*
 * ur 机械臂的dh 参数
 * https://www.universal-robots.com/articles/ur/application-installation/dh-parameters-for-calculations-of-kinematics-and-dynamics/
 */
double a2 = -0.425;
double a3 = -0.39225;

double alpha1 = PI / 2;
double alpha4 = PI / 2;
double alpha5 = -PI / 2;

double d1 = 0.089159;
double d4 = 0.10915;
double d5 = 0.09465;
double d6 = 0.0823;


int main() {
    Chain chain;

    // base link
    chain.addSegment(Segment(Joint(Joint::None), Frame(Vector(0, 0, d1))));

    // shoulder link
    Rotation rotation1(1, 0, 0, 0, cos(alpha1), -sin(alpha1), 0, sin(alpha1), cos(alpha1));
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(rotation1)));

    // upperarm link
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(Vector(a2, 0, 0))));

    // forearm link
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(Vector(a3, 0, d4))));

    // wrist1
    Rotation rotation2(1, 0, 0, 0, cos(alpha4), -sin(alpha4), 0, sin(alpha4), cos(alpha4));
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(rotation2) * Frame(Vector(0, 0, d5)))); // 先旋转 再平移

    // wrist2
    Rotation rotation3(1, 0, 0, 0, cos(alpha5), -sin(alpha5), 0, sin(alpha5), cos(alpha5));
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(rotation3) * Frame(Vector(0, 0, d6)))); // 先旋转 再平移

    // wrist3
    double d7 = 0; // 自己猜的!
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(Vector(0, 0, d7))));


    JntArray angles = JntArray(6);
    angles(0) = 0 * PI / 180;
    angles(1) = 0 * PI / 180;
    angles(2) = 0 * PI / 180;
    angles(3) = 0 * PI / 180;
    angles(4) = 0 * PI / 180;
    angles(5) = 0 * PI / 180;

    ChainFkSolverPos_recursive fk_solver(chain);
    Frame out;
    int state = fk_solver.JntToCart(angles, out); // Jnt:Joint , Cart:笛卡尔
    if (state >= 0) { // 有解
        // 这里使用 frame_io
        cout << out.M << endl;
        cout << out.p << endl;

        // 姿态
        double roll;
        double pitch;
        double yaw;
        out.M.GetRPY(roll, pitch, yaw);
        cout << roll << endl;
        cout << pitch << endl;
        cout << yaw << endl;

//        for (int i = 0; i < 9; ++i) {
//            cout << out.M.data[i] << "         ";
//            if (i % 3 == 2)
//                cout << endl;
//        }
//        cout << "===" << endl;
//        for (int i = 0; i < 3; ++i) {
//            cout << out.p.data[i] << endl;
//        }


    }


}

