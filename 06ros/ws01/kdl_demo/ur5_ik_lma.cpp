//
// Created by zcb on 4/17/21.
//

#include <iostream>
#include <kdl/chain.hpp>
#include <kdl/chainiksolverpos_lma.hpp>

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


    //  反解
    ChainIkSolverPos_LMA ik_solver(chain);

    JntArray cur_angles(6); // 当前 angle
    cur_angles(0) = 0 * PI / 180;
    cur_angles(1) = 0 * PI / 180;
    cur_angles(2) = 0 * PI / 180;
    cur_angles(3) = 0 * PI / 180;
    cur_angles(4) = 0 * PI / 180;
    cur_angles(5) = 0 * PI / 180;

    Frame dst_pos_ges(Rotation(1, 0, 0, 0, 1, 0, 0, 0, 1),
                      Vector(0.3, 0.3, 0.3));
    // 要给当前的关节角。因为反解很多,会给出距离当前最近的一种
    JntArray out_angles(6);
    int state = ik_solver.CartToJnt(cur_angles, dst_pos_ges, out_angles);
    if (state >= 0) {
        // 打印6个 angle
        for (int i = 0; i < 6; ++i) {
            cout << out_angles.data(i,0) * 180 / PI << endl; // 默认 第一个解
        }

        //cout << out_angles.data << endl;
        // out_angles 是 （6，n） 的矩阵,n 是解的个数
        cout << "解的个数" << out_angles.columns() << endl;


    } else {
        cout << "无解" << endl;
    }


}

