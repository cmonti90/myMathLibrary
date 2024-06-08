#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "myMathQuaternion.h"

BOOST_AUTO_TEST_SUITE( test_myMathQuaternion )


BOOST_AUTO_TEST_CASE( test_Quaternion_DefaultConstructor )
{
    myMath::Quaternion< double > q;

    BOOST_CHECK_SMALL( q.w() - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.x() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.y() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.z() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_Constructor )
{
    myMath::Quaternion< double > q( 1.0, 2.0, 3.0, 4.0 );

    BOOST_CHECK_SMALL( q.w() - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.x() - 2.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.y() - 3.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q.z() - 4.0, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_AggregateConstructor )
{
    const double q1[4] { 1.0, 2.0, 3.0, 4.0 };
    myMath::Quaternion< double > q2( q1 );

    BOOST_CHECK_SMALL( q2.w() - q1[0], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.x() - q1[1], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.y() - q1[2], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.z() - q1[3], 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_CopyConstructor )
{
    const myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );
    myMath::Quaternion< double > q2( q1 );

    BOOST_CHECK_SMALL( q2.w() - q1.w(), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.x() - q1.x(), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.y() - q1.y(), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.z() - q1.z(), 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_VectorConstructor )
{
    const myMath::Vector4d q1 { 1.0, 2.0, 3.0, 4.0 };
    myMath::Quaternion< double > q2( q1 );

    BOOST_CHECK_SMALL( q2.w() - q1[0], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.x() - q1[1], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.y() - q1[2], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.z() - q1[3], 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_ScalarAndVectorConstructor )
{
    const double w = 1.0;
    const myMath::Vector3d v { 2.0, 3.0, 4.0 };
    myMath::Quaternion< double > q2( w, v );

    BOOST_CHECK_SMALL( q2.w() - w, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.x() - v[0], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.y() - v[1], 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.z() - v[2], 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_AngleAndAxisConstructor )
{
    const double v = myMath::Constants::PI / 6.0;
    myMath::Quaternion< double > q2( v, myMath::Axis::X );

    BOOST_CHECK_SMALL( q2.w() - 0.965925826289068, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.x() - 0.258819045102521, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.y() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.z() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );


    myMath::Quaternion< double > q3( v, myMath::Axis::Y );;

    BOOST_CHECK_SMALL( q3.w() - 0.965925826289068, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.x() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.y() - 0.258819045102521, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.z() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );


    myMath::Quaternion< double > q4( v, myMath::Axis::Z );

    BOOST_CHECK_SMALL( q4.w() - 0.965925826289068, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q4.x() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q4.y() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q4.z() - 0.258819045102521, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_Multiplication )
{
    const myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );
    const myMath::Quaternion< double > q2( 5.0, 6.0, 7.0, 8.0 );
    const myMath::Quaternion< double > q3 = q1 * q2;

    BOOST_CHECK_SMALL( q3.w() +  60.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.x() -  12.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.y() -  30.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.z() -  24.0, 10.0 * std::numeric_limits< double >::epsilon() );

    const myMath::Quaternion< double > q4 = 2.0 * q1;
    const myMath::Quaternion< double > q5 = q1 * 2.0;

    BOOST_CHECK_SMALL( q4.w() - 2.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q4.x() - 4.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q4.y() - 6.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q4.z() - 8.0, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_MultiplicationAssignment )
{
    myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );
    myMath::Quaternion< double > q2( 5.0, 6.0, 7.0, 8.0 );
    q1 *= q2;

    BOOST_CHECK_SMALL( q1.w() +  60.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q1.x() -  12.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q1.y() -  30.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q1.z() -  24.0, 10.0 * std::numeric_limits< double >::epsilon() );

    myMath::Quaternion< double > q3( 1.0, 2.0, 3.0, 4.0 );
    q3 *= 2.0;

    BOOST_CHECK_SMALL( q3.w() - 2.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.x() - 4.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.y() - 6.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q3.z() - 8.0, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_Identity )
{
    const myMath::Quaternion< double > q1 = myMath::Quaternion< double >::Identity();

    BOOST_CHECK_SMALL( q1.w() - 1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q1.x() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q1.y() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q1.z() - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
}



BOOST_AUTO_TEST_CASE( test_Quaternion_Conjugate )
{
    const myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );
    const myMath::Quaternion< double > q2 = q1.Conjugate();

    BOOST_CHECK_SMALL( q2.w() -  1.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.x() - -2.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.y() - -3.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.z() - -4.0, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_Inverse )
{
    const myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );
    const myMath::Quaternion< double > q2 = q1.Inverse();

    BOOST_CHECK_SMALL( q2.w() -  0.0333333333333333, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.x() - -0.0666666666666667, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.y() - -0.1, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.z() - -0.133333333333333, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_ToDCM )
{
    const myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );

    const myMath::Matrix3d dcm = q1.ToDCM();

    BOOST_CHECK_SMALL( dcm( 0, 0 ) - -0.666666666666667, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 1 ) -  0.666666666666667, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 0, 2 ) -  0.333333333333333, 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 1, 0 ) -  0.133333333333333, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 1 ) - -0.333333333333333, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 1, 2 ) -  0.933333333333333, 10.0 * std::numeric_limits< double >::epsilon() );

    BOOST_CHECK_SMALL( dcm( 2, 0 ) -  0.733333333333333, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 1 ) -  0.666666666666667, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( dcm( 2, 2 ) -  0.133333333333333, 10.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_ToAngle_TaitBryanOrder )
{
    // Check identity quaternion
    const myMath::Quaternion< double > qIdentity( myMath::QuaternionD::Identity() );
    const myMath::AngleD anglesIdentity = qIdentity.ToAngle( myMath::TaitBryanOrder::XYZ );

    BOOST_CHECK_SMALL( anglesIdentity[0] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( anglesIdentity[1] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( anglesIdentity[2] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );


    const myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );

    // XYZ
    myMath::Angle< double > angles = q1.ToAngle( myMath::TaitBryanOrder::XYZ );

    BOOST_CHECK_SMALL( angles[0] - ( -1.373400766945016 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  0.823211977125876 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - ( -2.944197093739913 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // XZY
    angles = q1.ToAngle( myMath::TaitBryanOrder::XZY );

    BOOST_CHECK_SMALL( angles[0] - (  1.913820267215600 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - ( -0.133731589409942 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  2.308611386915361 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YXZ
    angles = q1.ToAngle( myMath::TaitBryanOrder::YXZ );

    BOOST_CHECK_SMALL( angles[0] - (  1.390942827002418 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - ( -0.729727656226966 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  2.034443935795703 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YZX
    angles = q1.ToAngle( myMath::TaitBryanOrder::YZX );

    BOOST_CHECK_SMALL( angles[0] - ( -2.677945044588987 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  0.729727656226966 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - ( -2.034443935795703 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZXY
    angles = q1.ToAngle( myMath::TaitBryanOrder::ZXY );

    BOOST_CHECK_SMALL( angles[0] - ( -2.761086276477428 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  1.203588306237060 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - ( -1.190289949682532 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZYX
    angles = q1.ToAngle( myMath::TaitBryanOrder::ZYX );

    BOOST_CHECK_SMALL( angles[0] - (  2.356194490192345 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - ( -0.339836909454122 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  1.428899272190733 ), 10.0 * std::numeric_limits< double >::epsilon() );


}


BOOST_AUTO_TEST_CASE( test_Quaternion_ToAngle_EulerOrder )
{
    // Check identity quaternion
    const myMath::Quaternion< double > qIdentity( myMath::QuaternionD::Identity() );
    const myMath::AngleD anglesIdentity = qIdentity.ToAngle( myMath::EulerOrder::XYX );

    BOOST_CHECK_SMALL( anglesIdentity[0] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( anglesIdentity[1] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( anglesIdentity[2] - 0.0, 10.0 * std::numeric_limits< double >::epsilon() );


    const myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );

    // XYX
    myMath::Angle< double > angles = q1.ToAngle( myMath::EulerOrder::XYX );

    BOOST_CHECK_SMALL( angles[0] - (  2.034443935795703 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  2.300523983021863 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  0.179853499792478 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // XZX
    angles = q1.ToAngle( myMath::EulerOrder::XZX );

    BOOST_CHECK_SMALL( angles[0] - (  0.463647609000806 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  2.300523983021863 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  1.750649826587375 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YXY
    angles = q1.ToAngle( myMath::EulerOrder::YXY );

    BOOST_CHECK_SMALL( angles[0] - (  0.141897054604164 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  1.910633236249019 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  2.356194490192345 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // YZY
    angles = q1.ToAngle( myMath::EulerOrder::YZY );

    BOOST_CHECK_SMALL( angles[0] - (  1.712693381399061 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  1.910633236249019 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  0.785398163397448 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZXZ
    angles = q1.ToAngle( myMath::EulerOrder::ZXZ );

    BOOST_CHECK_SMALL( angles[0] - (  2.308611386915361 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  1.437064737384955 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  0.343023940420703 ), 10.0 * std::numeric_limits< double >::epsilon() );


    // ZYZ
    angles = q1.ToAngle( myMath::EulerOrder::ZYZ );

    BOOST_CHECK_SMALL( angles[0] - (  0.737815060120465 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[1] - (  1.437064737384955 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( angles[2] - (  1.913820267215600 ), 10.0 * std::numeric_limits< double >::epsilon() );

}


BOOST_AUTO_TEST_CASE( test_Quaternion_Rotate )
{
    myMath::Quaternion< double > q1( myMath::QuaternionD::Identity() );
    const myMath::Vector3d v1 { -2.0, 6.0, 0.4 };

    myMath::Vector3d v2 = q1.Rotate( v1, myMath::RotType::PASSIVE );

    BOOST_CHECK_SMALL( v2[0] - v1[0], 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( v2[1] - v1[1], 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( v2[2] - v1[2], 100.0 * std::numeric_limits< double >::epsilon() );

    q1 = myMath::QuaternionD( 1.0, 2.0, 3.0, 4.0 );

    v2 = q1.Rotate( v1, myMath::RotType::PASSIVE );

    BOOST_CHECK_SMALL( v2[0] - (  2.426666666666666 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( v2[1] - ( -3.066666666666666 ), 100.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( v2[2] - (  4.986666666666665 ), 100.0 * std::numeric_limits< double >::epsilon() );
}


BOOST_AUTO_TEST_CASE( test_Quaternion_Derivative )
{
    const myMath::Quaternion< double > q1( 1.0, 2.0, 3.0, 4.0 );
    const myMath::Vector3d omega { 0.1, 0.2, 0.3 };

    const myMath::Quaternion< double > q2 = q1.Deriv( omega );

    BOOST_CHECK_SMALL( q2.w() - ( -1.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.x() - (  0.1 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.y() - (  0.0 ), 10.0 * std::numeric_limits< double >::epsilon() );
    BOOST_CHECK_SMALL( q2.z() - (  0.2 ), 10.0 * std::numeric_limits< double >::epsilon() );
}



BOOST_AUTO_TEST_SUITE_END()