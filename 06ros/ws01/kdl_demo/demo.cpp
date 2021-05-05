#include <iostream>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>

using namespace std;
using namespace KDL;
/*
 *  例子链接： https://medium.com/@sarvagya.vaish/forward-kinematics-using-orocos-kdl-da7035f9c8e
 * */


int main() {
    Chain chain;

    // link 0 // 每个link 都固连一个坐标系, link0 是base 坐标系     两个参数:joint:当前坐标系能不能转，能转的话指明旋转轴. frame:当前坐标系如何变换到下个坐标系
    chain.addSegment(Segment(Joint(Joint::None), Frame(Vector(0, 1, 0))));

    // link 1
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(Vector(0, 2, 0))));

    // link 2                                                                                                      先旋转  后平移
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(Rotation::EulerZYX(0, 0, -PI / 2)) * Frame(Vector(0, 0, 2))));

    // link 3          // link3 的坐标系 的下一个是 tool 坐标系
    chain.addSegment(Segment(Joint(Joint::RotZ), Frame(Rotation::EulerZYX(0, 0, PI / 2)) * Frame(Vector(1, 1, 0))));


    JntArray angles = JntArray(3);
    angles(0) = -PI / 4;
    angles(1) = PI / 2;
    angles(2) = PI;

    ChainFkSolverPos_recursive fk_solver(chain);
    Frame out;
    fk_solver.JntToCart(angles, out);
    for (int i = 0; i < 9; ++i) {
        cout << out.M.data[i] << "         ";
        if (i % 3 == 2)
            cout << endl;
    }
    cout << "===" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << out.p.data[i] << endl;
    }

    return 0;
}
