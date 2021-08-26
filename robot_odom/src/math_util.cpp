#include "math_util.h"
#include <sys/time.h>
#include <unistd.h>

#ifndef PI
#define PI 3.141592653589793
#endif

#ifndef PI_2
#define PI_2 6.283185307179586
#endif

double cos_values[361] = {
 1.0000, 0.9998, 0.9994, 0.9986, 0.9976, 0.9962, 0.9945, 0.9925, 0.9903, 0.9877,
 0.9848, 0.9816, 0.9781, 0.9744, 0.9703, 0.9659, 0.9613, 0.9563, 0.9511, 0.9455,
 0.9397, 0.9336, 0.9272, 0.9205, 0.9135, 0.9063, 0.8988, 0.8910, 0.8829, 0.8746,
 0.8660, 0.8572, 0.8480, 0.8387, 0.8290, 0.8192, 0.8090, 0.7986, 0.7880, 0.7771,
 0.7660, 0.7547, 0.7431, 0.7314, 0.7193, 0.7071, 0.6947, 0.6820, 0.6691, 0.6561,
 0.6428, 0.6293, 0.6157, 0.6018, 0.5878, 0.5736, 0.5592, 0.5446, 0.5299, 0.5150,
 0.5000, 0.4848, 0.4695, 0.4540, 0.4384, 0.4226, 0.4067, 0.3907, 0.3746, 0.3584,
 0.3420, 0.3256, 0.3090, 0.2924, 0.2756, 0.2588, 0.2419, 0.2250, 0.2079, 0.1908,
 0.1736, 0.1564, 0.1392, 0.1219, 0.1045, 0.0872, 0.0698, 0.0523, 0.0349, 0.0175,
 0.0000,-0.0175,-0.0349,-0.0523,-0.0698,-0.0872,-0.1045,-0.1219,-0.1392,-0.1564,
-0.1736,-0.1908,-0.2079,-0.2250,-0.2419,-0.2588,-0.2756,-0.2924,-0.3090,-0.3256,
-0.3420,-0.3584,-0.3746,-0.3907,-0.4067,-0.4226,-0.4384,-0.4540,-0.4695,-0.4848,
-0.5000,-0.5150,-0.5299,-0.5446,-0.5592,-0.5736,-0.5878,-0.6018,-0.6157,-0.6293,
-0.6428,-0.6561,-0.6691,-0.6820,-0.6947,-0.7071,-0.7193,-0.7314,-0.7431,-0.7547,
-0.7660,-0.7771,-0.7880,-0.7986,-0.8090,-0.8192,-0.8290,-0.8387,-0.8480,-0.8572,
-0.8660,-0.8746,-0.8829,-0.8910,-0.8988,-0.9063,-0.9135,-0.9205,-0.9272,-0.9336,
-0.9397,-0.9455,-0.9511,-0.9563,-0.9613,-0.9659,-0.9703,-0.9744,-0.9781,-0.9816,
-0.9848,-0.9877,-0.9903,-0.9925,-0.9945,-0.9962,-0.9976,-0.9986,-0.9994,-0.9998,
-1.0000,-0.9998,-0.9994,-0.9986,-0.9976,-0.9962,-0.9945,-0.9925,-0.9903,-0.9877,
-0.9848,-0.9816,-0.9781,-0.9744,-0.9703,-0.9659,-0.9613,-0.9563,-0.9511,-0.9455,
-0.9397,-0.9336,-0.9272,-0.9205,-0.9135,-0.9063,-0.8988,-0.8910,-0.8829,-0.8746,
-0.8660,-0.8572,-0.8480,-0.8387,-0.8290,-0.8192,-0.8090,-0.7986,-0.7880,-0.7771,
-0.7660,-0.7547,-0.7431,-0.7314,-0.7193,-0.7071,-0.6947,-0.6820,-0.6691,-0.6561,
-0.6428,-0.6293,-0.6157,-0.6018,-0.5878,-0.5736,-0.5592,-0.5446,-0.5299,-0.5150,
-0.5000,-0.4848,-0.4695,-0.4540,-0.4384,-0.4226,-0.4067,-0.3907,-0.3746,-0.3584,
-0.3420,-0.3256,-0.3090,-0.2924,-0.2756,-0.2588,-0.2419,-0.2250,-0.2079,-0.1908,
-0.1736,-0.1564,-0.1392,-0.1219,-0.1045,-0.0872,-0.0698,-0.0523,-0.0349,-0.0175,
-0.0000, 0.0175, 0.0349, 0.0523, 0.0698, 0.0872, 0.1045, 0.1219, 0.1392, 0.1564,
 0.1736, 0.1908, 0.2079, 0.2250, 0.2419, 0.2588, 0.2756, 0.2924, 0.3090, 0.3256,
 0.3420, 0.3584, 0.3746, 0.3907, 0.4067, 0.4226, 0.4384, 0.4540, 0.4695, 0.4848,
 0.5000, 0.5150, 0.5299, 0.5446, 0.5592, 0.5736, 0.5878, 0.6018, 0.6157, 0.6293,
 0.6428, 0.6561, 0.6691, 0.6820, 0.6947, 0.7071, 0.7193, 0.7314, 0.7431, 0.7547,
 0.7660, 0.7771, 0.7880, 0.7986, 0.8090, 0.8192, 0.8290, 0.8387, 0.8480, 0.8572,
 0.8660, 0.8746, 0.8829, 0.8910, 0.8988, 0.9063, 0.9135, 0.9205, 0.9272, 0.9336,
 0.9397, 0.9455, 0.9511, 0.9563, 0.9613, 0.9659, 0.9703, 0.9744, 0.9781, 0.9816,
 0.9848, 0.9877, 0.9903, 0.9925, 0.9945, 0.9962, 0.9976, 0.9986, 0.9994, 0.9998,
1.0000};
double sin_values[361] = {
 0.0000, 0.0175, 0.0349, 0.0523, 0.0698, 0.0872, 0.1045, 0.1219, 0.1392, 0.1564,
 0.1736, 0.1908, 0.2079, 0.2250, 0.2419, 0.2588, 0.2756, 0.2924, 0.3090, 0.3256,
 0.3420, 0.3584, 0.3746, 0.3907, 0.4067, 0.4226, 0.4384, 0.4540, 0.4695, 0.4848,
 0.5000, 0.5150, 0.5299, 0.5446, 0.5592, 0.5736, 0.5878, 0.6018, 0.6157, 0.6293,
 0.6428, 0.6561, 0.6691, 0.6820, 0.6947, 0.7071, 0.7193, 0.7314, 0.7431, 0.7547,
 0.7660, 0.7771, 0.7880, 0.7986, 0.8090, 0.8192, 0.8290, 0.8387, 0.8480, 0.8572,
 0.8660, 0.8746, 0.8829, 0.8910, 0.8988, 0.9063, 0.9135, 0.9205, 0.9272, 0.9336,
 0.9397, 0.9455, 0.9511, 0.9563, 0.9613, 0.9659, 0.9703, 0.9744, 0.9781, 0.9816,
 0.9848, 0.9877, 0.9903, 0.9925, 0.9945, 0.9962, 0.9976, 0.9986, 0.9994, 0.9998,
 1.0000, 0.9998, 0.9994, 0.9986, 0.9976, 0.9962, 0.9945, 0.9925, 0.9903, 0.9877,
 0.9848, 0.9816, 0.9781, 0.9744, 0.9703, 0.9659, 0.9613, 0.9563, 0.9511, 0.9455,
 0.9397, 0.9336, 0.9272, 0.9205, 0.9135, 0.9063, 0.8988, 0.8910, 0.8829, 0.8746,
 0.8660, 0.8572, 0.8480, 0.8387, 0.8290, 0.8192, 0.8090, 0.7986, 0.7880, 0.7771,
 0.7660, 0.7547, 0.7431, 0.7314, 0.7193, 0.7071, 0.6947, 0.6820, 0.6691, 0.6561,
 0.6428, 0.6293, 0.6157, 0.6018, 0.5878, 0.5736, 0.5592, 0.5446, 0.5299, 0.5150,
 0.5000, 0.4848, 0.4695, 0.4540, 0.4384, 0.4226, 0.4067, 0.3907, 0.3746, 0.3584,
 0.3420, 0.3256, 0.3090, 0.2924, 0.2756, 0.2588, 0.2419, 0.2250, 0.2079, 0.1908,
 0.1736, 0.1564, 0.1392, 0.1219, 0.1045, 0.0872, 0.0698, 0.0523, 0.0349, 0.0175,
 0.0000,-0.0175,-0.0349,-0.0523,-0.0698,-0.0872,-0.1045,-0.1219,-0.1392,-0.1564,
-0.1736,-0.1908,-0.2079,-0.2250,-0.2419,-0.2588,-0.2756,-0.2924,-0.3090,-0.3256,
-0.3420,-0.3584,-0.3746,-0.3907,-0.4067,-0.4226,-0.4384,-0.4540,-0.4695,-0.4848,
-0.5000,-0.5150,-0.5299,-0.5446,-0.5592,-0.5736,-0.5878,-0.6018,-0.6157,-0.6293,
-0.6428,-0.6561,-0.6691,-0.6820,-0.6947,-0.7071,-0.7193,-0.7314,-0.7431,-0.7547,
-0.7660,-0.7771,-0.7880,-0.7986,-0.8090,-0.8192,-0.8290,-0.8387,-0.8480,-0.8572,
-0.8660,-0.8746,-0.8829,-0.8910,-0.8988,-0.9063,-0.9135,-0.9205,-0.9272,-0.9336,
-0.9397,-0.9455,-0.9511,-0.9563,-0.9613,-0.9659,-0.9703,-0.9744,-0.9781,-0.9816,
-0.9848,-0.9877,-0.9903,-0.9925,-0.9945,-0.9962,-0.9976,-0.9986,-0.9994,-0.9998,
-1.0000,-0.9998,-0.9994,-0.9986,-0.9976,-0.9962,-0.9945,-0.9925,-0.9903,-0.9877,
-0.9848,-0.9816,-0.9781,-0.9744,-0.9703,-0.9659,-0.9613,-0.9563,-0.9511,-0.9455,
-0.9397,-0.9336,-0.9272,-0.9205,-0.9135,-0.9063,-0.8988,-0.8910,-0.8829,-0.8746,
-0.8660,-0.8572,-0.8480,-0.8387,-0.8290,-0.8192,-0.8090,-0.7986,-0.7880,-0.7771,
-0.7660,-0.7547,-0.7431,-0.7314,-0.7193,-0.7071,-0.6947,-0.6820,-0.6691,-0.6561,
-0.6428,-0.6293,-0.6157,-0.6018,-0.5878,-0.5736,-0.5592,-0.5446,-0.5299,-0.5150,
-0.5000,-0.4848,-0.4695,-0.4540,-0.4384,-0.4226,-0.4067,-0.3907,-0.3746,-0.3584,
-0.3420,-0.3256,-0.3090,-0.2924,-0.2756,-0.2588,-0.2419,-0.2250,-0.2079,-0.1908,
-0.1736,-0.1564,-0.1392,-0.1219,-0.1045,-0.0872,-0.0698,-0.0523,-0.0349,-0.0175,
-0.0000};

double * lms100_cos = NULL;
double * lms100_sin = NULL;

void math_init_lms_tri_table (double startAngleDeg, double angularResolDeg, int count)
{
	double curAngleDeg = 0;
	double curAngleRad = 0;

	lms100_cos = (double *) malloc(sizeof(double) * count);
	lms100_sin = (double *) malloc(sizeof(double) * count);

	for(int i = 0; i < count; i++)
	{
		curAngleDeg = i*angularResolDeg + startAngleDeg;
		curAngleRad = to_rad(curAngleDeg);
		
		lms100_cos[i] = cos(curAngleRad);
		lms100_sin[i] = sin(curAngleRad);
	}
	curAngleDeg = curAngleDeg;
}

void math_clear_lms_tri_table()
{
	if(lms100_cos) free(lms100_cos);
	if(lms100_sin) free(lms100_sin);

	lms100_cos = NULL;
	lms100_sin = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// random utility function
///////////////////////////////////////////////////////////////////////////////
double unit_rand()
{
	return (abs(rand()) % 1000) / 1000.0;
}

int rand_perm(int n)
{
	return (abs(rand()) % n);
}

///////////////////////////////////////////////////////////////////////////////
// coordination transform functions
///////////////////////////////////////////////////////////////////////////////
void math_generate_rpy_mat_deg(double * prot, double roll, double pitch, double yaw)
{
	return math_generate_rpy_mat_rad(prot, to_rad(roll), to_rad(pitch), to_rad(yaw));
}

void math_generate_rpy_mat_rad(double * prot, double roll, double pitch, double yaw)
{
        prot[0] =  cos( roll ) * cos( pitch );
        prot[1] =  cos( roll ) * sin( yaw ) - sin( roll ) * cos( yaw );
        prot[2] =  cos( roll ) * sin( pitch ) * cos( yaw) + sin( roll ) * sin( yaw );
        
	prot[3] =  sin( roll ) * cos( pitch );
        prot[4] =  sin( roll ) * sin( pitch ) * sin( yaw ) + cos( roll ) * cos( yaw );
        prot[5] =  sin( roll ) * sin( pitch ) * cos( yaw ) - cos( roll ) * sin( yaw );
        
	prot[6] = -sin( pitch );
        prot[7] =  cos( pitch ) * sin( yaw );
        prot[8] =  cos( pitch ) * cos( yaw );
}

void math_compute_rpy(double * prot, double local_x,  double local_y,  double local_z, 
		                     double offset_x, double offset_y, double offset_z, 
				     double * px,     double * py,     double * pz)
{
        *px = prot[0] * local_x + prot[1] * local_y + prot[2] * local_z + offset_x;
        *py = prot[3] * local_x + prot[4] * local_y + prot[5] * local_z + offset_y;
        *pz = prot[6] * local_x + prot[7] * local_y + prot[8] * local_z + offset_z;
}

///////////////////////////////////////////////////////////////////////////////
// math utility function
///////////////////////////////////////////////////////////////////////////////
double math_heading_diff_rad(double refAngleRad, double nxtAngleRad)
{
	//case refAngle = 6deg, nxtAngle = -5 -> (nxtAngle - refAngle) = (-5 - 6) = -9 deg , sol = -9
	//case refAngle = -6deg, nxtAngle = 6 -> (nxtAngle - refAngle) = (6 + 6) = 12 deg , sol = 12
	//case refAngle = 170deg, nxtAngle = -135 -> (nxtAngle - refAngle) = (-135 - 170) = -305 deg , normal angle = -305 + 360 = 55deg
	//case refAngle = 170deg, nxtAngle = -170 -> (nxtAngle - refAngle) = (-170 - 170) = -340 deg , normal angle = -340 + 360 = 20deg
	//case refAngle = -170deg, nxtAngle = 170 -> (nxtAngle - refAngle) = (170 - (-170)) = 340 deg , normal angle = 340 - 360 = -20deg
	
	double delTheta =  nxtAngleRad - refAngleRad;
        
	if(fabs(delTheta) > PI)
        {
                if(delTheta > 0)
                {
                        delTheta -= 2.0f * PI;
                }
                else
                {
                        delTheta += 2.0f * PI;
                }
        }
        return delTheta;
}

double math_heading_diff_deg(double refAngleRad, double nxtAngleRad)
{
	double delTheta =  nxtAngleRad - refAngleRad;
        
	if(fabs(delTheta) > 180)
        {
                if(delTheta > 0)
                {
                        delTheta -= 360;
                }
                else
                {
                        delTheta += 360;
                }
        }
        return delTheta;
}

void math_local_del_pose_rad(double refX, double refY, double refThRad, double nxtX, double nxtY, double nxtThRad, double * pDelX, double *pDelY, double *pDelThRad)
{
	double tmpDelX = nxtX - refX;
	double tmpDelY = nxtY - refY;
	double rotC = cos(-refThRad);
	double rotS = sin(-refThRad);

	*pDelThRad	= math_heading_diff_rad(refThRad, nxtThRad);
	
	*pDelX =  tmpDelX * rotC - tmpDelY * rotS;
	*pDelY =  tmpDelX * rotS + tmpDelY * rotC;
}

void math_local_del_pose_deg(double refX, double refY, double refThDeg, double nxtX, double nxtY, double nxtThDeg, double * pDelX, double *pDelY, double *pDelThDeg)
{
	double refThRad = to_rad(refThDeg);
	double nxtThRad = to_rad(nxtThDeg);

	math_local_del_pose_rad(refX, refY, refThRad, nxtX, nxtY, nxtThRad, pDelX, pDelY, pDelThDeg);
	*pDelThDeg = to_deg(*pDelThDeg);
}

int round_i(double num)
{
	return (int) ((num < 0) ? (num - 0.5f) : (num + 0.5f));	
}

double round_d(double num)
{
	return (double) ((int) ((num < 0) ? (num - 0.5f) : (num + 0.5f)));	
}

float round_f(float num)
{
	return (float) ((int) ((num < 0) ? (num - 0.5f) : (num + 0.5f)));	
}

///////////////////////////////////////////////////////////////////////////////
// time functions
///////////////////////////////////////////////////////////////////////////////
double time_milli_sec()
{
#ifdef _WIN32
	DWORD dwCurTime;
	dwCurTime = timeGetTime();
	return (double) dwCurTime;
#else
        struct timeval tv;
        gettimeofday(&tv,NULL);
        return ((tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0));
#endif
}

unsigned long time_milli_sec_ulong()
{
#ifdef _WIN32
	DWORD dwCurTime;
	dwCurTime = timeGetTime();
	return (unsigned long)dwCurTime;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0));
#endif
}

///////////////////////////////////////////////////////////////////////////////
//Motion Utility Functions
///////////////////////////////////////////////////////////////////////////////
int motion_wheel_vel(double tr_vel_m, double rot_vel_deg, double * pleft_vel, double * pright_vel)
{
	/*
	double rot_vel_rad = to_rad(rot_vel_deg);
	
	double wheel_base = (TETRA_WHEEL_BASE / 1000.0); //mm
	double vel_right = 0.0f;
	double vel_left  = 0.0f;
	
	vel_right = tr_vel_m + (rot_vel_rad * wheel_base) / 2.0;
	vel_left  = 2.0f * tr_vel_m - vel_right;

	*pleft_vel  = vel_left;
	*pright_vel = vel_right;
	*/
	return 0;
}

double motion_normalize_heading_rad(double theta_rad)
{
	double theta = theta_rad;
	
	if( theta > PI) 
	{
		theta-=PI_2;
	}
	else if( theta < -PI) 
	{
		theta += PI_2;
	}
	return theta;
}

double motion_normalize_heading_deg(double deg)
{
	double theta = deg;
	
	if( theta > 180.0f) 
	{
		theta-=360.0f;
	}
	else if( theta < -180.0f) 
	{
		theta += 360.0f;
	}
	return theta;
}

double motion_compute_heading_diff(
	double targetPoseX, double targetPoseY, double targetPoseTh_rad,
	double curPoseX, double curPoseY, double curTh_rad, 
	double delPoseX, double delPoseY, double deltaThetaRad)
{
	double dHeadingDiff = 0;

	double resultTheta_rad = 0;
	double delThetaToTarget_rad = 0;
	double delX = 0;
	double delY = 0;
		
	delX = targetPoseX-(curPoseX+delPoseX);
	delY = targetPoseY-(curPoseY+delPoseY);

	
	delThetaToTarget_rad = atan2(delY, delX);
        resultTheta_rad      = deltaThetaRad+curTh_rad;
        resultTheta_rad      = motion_normalize_heading_rad(resultTheta_rad);

        double delTheta = 0.0f;

        delTheta =  delThetaToTarget_rad - resultTheta_rad;
        if(fabs(delTheta) > PI)
        {
                if(delTheta > 0)
                {
                        delTheta -= 2.0f * PI;
                }
                else
                {
                        delTheta += 2.0f * PI;
                }
        }
        dHeadingDiff = delTheta;
        
	return dHeadingDiff;
}

double motion_compute_next_pose
(
	double x_mm, 
	double y_mm, 
	double th_deg, 
	double time_step_sec,
	double v_tr_m_sec,
	double v_rot_deg_sec, 
	double *px_mm, 
	double *py_mm, 
	double *pth_deg_mm
)
{
	double del_pose[3] = {0};
	
	double moving_dist = 0;	

	//caution :: translational velocity unit is mm
	double tr_vel_step    = v_tr_m_sec    * time_step_sec * 1000.0f;
	double rot_vel_step   = v_rot_deg_sec * time_step_sec;
	double rot_vel_step_2 = v_rot_deg_sec * time_step_sec * 0.5;
	
	del_pose[2] = rot_vel_step;
	
	int theta1 = 0;	
	theta1 = (int) floor(th_deg + rot_vel_step_2 + 0.5);
        
        while(1)
        {
                if(theta1 >= 0 && theta1 < 360)
                {
                        break;
                }
                
	        if(theta1 < 0)
                {
                       theta1 = theta1 + 360;
                }
                else if(theta1 >= 360)
                {
                        theta1 = theta1 - 360;
                }
        }
        del_pose[0] = tr_vel_step * cos_values[theta1];
	del_pose[1] = tr_vel_step * sin_values[theta1];
	
	*px_mm = x_mm + del_pose[0];
	*py_mm = y_mm + del_pose[1];
	*pth_deg_mm = motion_normalize_heading_deg(th_deg + del_pose[2]);

        moving_dist = sqrt((double) ( del_pose[0] * del_pose[0] + del_pose[1] * del_pose[1]) ) ;

	return moving_dist;	
}

double compute_velocity_to_goal(double goal_x, double goal_y, double prev_x, double prev_y, double cur_x, double cur_y, double del_time /*sec*/) //unit is mm
{
	double return_velocity = 0.0;

	double inner_product = 0.0;
	double theta_rad     = 0.0;
	
	double goal_vec_x    = goal_x - prev_x;
	double goal_vec_y    = goal_y - prev_y;
	double pose_vec_x    = cur_x  - prev_x;
	double pose_vec_y    = cur_y  - prev_y;

	double norm_goal = sqrt( goal_vec_x * goal_vec_x + goal_vec_y * goal_vec_y);
	double norm_pose = sqrt( pose_vec_x * pose_vec_x + pose_vec_y * pose_vec_y);
	
	if( fabs(norm_goal) < 10.0 || fabs(norm_pose) < 10.0 )
	{
		return 0.0;
	}

	inner_product = goal_vec_x * pose_vec_x + goal_vec_y * pose_vec_y;
	theta_rad     = acos( inner_product / (norm_goal * norm_pose) );
	
	return_velocity = (norm_pose * cos(theta_rad) ) / del_time;

	return return_velocity;
}

///////////////////////////////////////////////////////////////////////////////
// vector functions
///////////////////////////////////////////////////////////////////////////////
double vec_norm(double * a, int n) //a must be a column vector
{
	return vec_norm_l2(a, n);
}

double vec_norm_l1(double * a, int n) //a must be a column vector
{
	double sum  = 0;
	for(int i = 0; i < n; i++)
	{
		sum += fabs(a[i]);
	}
	return sum;
}

double vec_norm_l2(double * a, int n) //a must be a column vector
{
	double norm = 0;
	double sum  = 0;
	for(int i = 0; i < n; i++)
	{
		sum += a[i]*a[i];
	}
	norm = sqrt( (double) sum );
	return norm;
}

double vec_norm_ln(double * a, int n) //a must be a column vector
{
	double norm = 0;
	double sum  = 0;
	for(int i = 0; i < n; i++)
	{
		sum += a[i]*a[i];
	}
	norm = pow( (double) sum, (double) 1/n );
	return norm;
}

double vec_norm_linf(double * a, int n) //a must be a column vector
{
	double norm = 0;
	double max  = 0;
	for(int i = 0; i < n; i++)
	{
		norm = fabs(a[i]);
		if(max < norm)
		{
			max = norm;
		}
	}
	return max;
}

double vec_angle(double * a, double * b, int n)
{
	double norm_a = 0;
	double norm_b = 0;
	
	double * a_tr;
	double a_b;

	double cos_value = 0;
	double theta     = 0;

	norm_a = vec_norm_ln(a, n);
	norm_b = vec_norm_ln(b, n);

	a_tr = (double*)calloc(n, sizeof(double));
	mat_transpose(a, n, 1, a_tr);
	
	if( (norm_a*norm_b) > 0.00001)
	{
		mat_multiply(a_tr, b, 1, n, 1, &a_b);
		cos_value = a_b / (norm_a * norm_b);
		
		theta = acos(cos_value);
		return theta;
	}
	else
	{
		return 0;
	}
}


///////////////////////////////////////////////////////////////////////////////
// matrix functions
///////////////////////////////////////////////////////////////////////////////
int mat_copy(double * A, double * B, int m, int n)
{
	// A = input matrix (m x n)
	// B = output matrix = A to B (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	int i, j;
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			B[n*i+j]=A[n*i+j];
		}
	}
	return 0;
}

int mat_add(double * a, double * b, int m, int n, double * ret)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A+B (m x n)
	int i, j;
	double * A = NULL;
	double * B = NULL;

	A = (double*)calloc(m*n, sizeof(double));
	B = (double*)calloc(m*n, sizeof(double));
	mat_copy(a, A, m, n);
	mat_copy(b, B, m, n);

	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			ret[n*i+j]=A[n*i+j]+B[n*i+j];
		}
	}

	free(A);
	free(B);

	return 0;
}


int mat_subtract(double * a, double * b, int m, int n, double * ret)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A-B (m x n)
	int i, j;
	double * A = NULL;
	double * B = NULL;

	A = (double*)calloc(m*n, sizeof(double));
	B = (double*)calloc(m*n, sizeof(double));
	mat_copy(a, A, m, n);
	mat_copy(b, B, m, n);

	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			ret[n*i+j]=A[n*i+j]-B[n*i+j];
		}
	}

	free(A);
	free(B);

	return 0;
}

int mat_multiply(double * a, double * b, int m, int p, int n, double * ret)
{
	// A = input matrix (m x p)
	// B = input matrix (p x n)
	// m = number of rows in A
	// p = number of columns in A = number of rows in B
	// n = number of columns in B
	// ret = output matrix = a*b (m x n)
	
	int i, j, k;
	double * A = NULL;
	double * B = NULL;

	A = (double*)calloc(m*p, sizeof(double));
	B = (double*)calloc(p*n, sizeof(double));
	mat_copy(a, A, m, p);
	mat_copy(b, B, p, n);

	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			ret[n*i+j]=0;
			for (k=0;k<p;k++)
			{
				ret[n*i+j]= ret[n*i+j]+A[p*i+k]*B[n*k+j];
			}
		}
	}

	free(A);
	free(B);

	return 0;
}

int mat_multiply3(double * a, double * b, double *c, int m, int p, int q, int n, double * ret)
{
	int i, j, k;
	double * A = NULL;
	double * B = NULL;
	double * C = NULL;
	
	double * tmp_ret = NULL;

	A = (double*)calloc(m*p, sizeof(double));
	B = (double*)calloc(p*q, sizeof(double));
	C = (double*)calloc(q*n, sizeof(double));
	
	tmp_ret = (double*)calloc(m*q, sizeof(double));

	mat_copy(a, A, m, p);
	mat_copy(b, B, p, q);
	mat_copy(c, C, q, n);

	for (i=0;i<m;i++)
	{
		for(j=0;j<q;j++)
		{
			tmp_ret[q*i+j]=0;
			for (k=0;k<p;k++)
			{
				tmp_ret[q*i+j]= tmp_ret[q*i+j]+A[p*i+k]*B[q*k+j];
			}
		}
	}
	
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			ret[n*i+j]=0;
			for (k=0;k<q;k++)
			{
				ret[n*i+j]= ret[n*i+j]+tmp_ret[q*i+k]*C[n*k+j];
			}
		}
	}

	free(A);
	free(B);
	free(C);
	free(tmp_ret);

	return 0;
}

double mat_determinent(double * a, int n)
{
	double * A = NULL;
	double * A_ij = NULL;
	double tmp = 0, det = 0;
	
	int co_idx = 0;
	int i = 0, j = 0;
	int idx_j = 0;

	if(n == 1)
	{
		det = a[0];
		return det;
	}

	if(n == 2)
	{
		det = a[0]*a[3] - a[1]*a[2];
		return det;
	}
	
	A = (double*)calloc(n*n, sizeof(double));
	A_ij = (double*)calloc((n-1)*(n-1), sizeof(double));

	mat_copy(a, A, n, n);
	
	for(co_idx = 0; co_idx < n; co_idx++)
	{
		for(i = 1; i < n; i++)
		{
			for(j = 0, idx_j = 0; j < n; j++)
			{
				if(co_idx == j)
				{
					continue;
				}
				A_ij[(i-1)*(n-1)+idx_j] = A[i*n + j];
				idx_j++;				
			}
		}
		tmp = A[0*n + co_idx] * pow( (double) -1, (double) 1+(co_idx+1)) * mat_determinent(A_ij, n-1);
		det += tmp;
	}

	free(A);
	free(A_ij);
	return det;
}

double mat_trace(double * a, int n)
{
	double trace = 0;
	int i = 0;
	for(i = 0; i < n; i++)
	{
		trace += a[i*n + i];
	}
	return trace;
}

double mat_abs_diff_sum(double * a, double * b, int m, int n)
{
	double sum = 0;
	int i = 0, j = 0;

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			sum += fabs(a[i*n + j]-b[i*n + j]);
		}
	}
	return sum;
}

double mat_abs_diff_max(double * a, double * b, int m, int n)
{
	double tmp = 0;
	double max = 0;
	int i = 0, j = 0;

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			tmp = fabs(a[i*n + j]-b[i*n + j]);
			if(max < tmp)
			{
				max = tmp;
			}
		}
	}
	return max;
}

double mat_diff_det(double * a, double * b, int m, int n)
{
	double sum = 0;
	int i = 0, j = 0;
	
	double * subtract;

	subtract = (double *) calloc(m*n, sizeof(double));
	mat_subtract(a, b, m, n, subtract);
	sum = mat_determinent(subtract, m);

	free(subtract);
	return sum;
}

int mat_transpose(double * a, int m, int n, double * ret)
{
	// A = input matrix (m x n)
	// m = number of rows in A
	// n = number of columns in A
	// C = output matrix = the transpose of A (n x m)
	int i, j;
	double * A = NULL;

	A = (double*)calloc(m*n, sizeof(double));
	mat_copy(a, A, m, n);

	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			ret[m*j+i]=A[n*i+j];
		}
	}

	free(A);

	return 0;
}

int mat_covariance(double * a, double * b, int n, double * ret)
{
	//A = input matrix(m * n)
	//n = number of dimension A
	double * transpose = (double*)calloc(n*n, sizeof(double));
	double * tmp = (double*)calloc(n*n, sizeof(double));
	double * A = NULL;
	double * B = NULL;

	A = (double*)calloc(n*n, sizeof(double));
	B = (double*)calloc(n*n, sizeof(double));
	mat_copy(a, A, n, n);
	mat_copy(b, B, n, n);


	mat_transpose(A, n, n, transpose);
	mat_multiply(B, transpose, n, n, n, tmp);
	mat_multiply(A, tmp, n, n, n, ret);
	
	free(transpose);
	free(tmp);


	free(A);
	free(B);

	return 0;
}

int mat_inverse(double * a, int n, double * AInverse)
{
	// A = input matrix (n x n)
	// n = dimension of A 
	// AInverse = inverted matrix (n x n)
	// This function inverts a matrix based on the Gauss Jordan method.
	// The function returns 1 on success, 0 on failure.
	int i, j, iPass, imx, icol, irow;
	double det, temp, pivot, factor;
	double * ac = (double*)calloc(n*n, sizeof(double));
	double * A = NULL;
	
	A = (double*)calloc(n*n, sizeof(double));
	mat_copy(a, A, n, n);

	det = 1;
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			AInverse[n*i+j] = 0;
			ac[n*i+j] = A[n*i+j];
		}
		AInverse[n*i+i] = 1;
	}

	// The current pivot row is iPass.  
	// For each pass, first find the maximum element in the pivot column.
	for (iPass = 0; iPass < n; iPass++)
	{
		imx = iPass;
		for (irow = iPass; irow < n; irow++)
		{
			if (fabs(A[n*irow+iPass]) > fabs(A[n*imx+iPass])) imx = irow;
		}
		// Interchange the elements of row iPass and row imx in both A and AInverse.
		if (imx != iPass)
		{
			for (icol = 0; icol < n; icol++)
			{
				temp = AInverse[n*iPass+icol];
				AInverse[n*iPass+icol] = AInverse[n*imx+icol];
				AInverse[n*imx+icol] = temp;
				if (icol >= iPass)
				{
					temp = A[n*iPass+icol];
					A[n*iPass+icol] = A[n*imx+icol];
					A[n*imx+icol] = temp;
				}
			}
		}
		// The current pivot is now A[iPass][iPass].
		// The determinant is the product of the pivot elements.
		pivot = A[n*iPass+iPass];
		det = det * pivot;
		if (det == 0) 
		{
			free(ac);
			return 0;
		}

		for (icol = 0; icol < n; icol++)
		{
			// Normalize the pivot row by dividing by the pivot element.
			AInverse[n*iPass+icol] = AInverse[n*iPass+icol] / pivot;
			if (icol >= iPass) A[n*iPass+icol] = A[n*iPass+icol] / pivot;
		}

		for (irow = 0; irow < n; irow++)
		// Add a multiple of the pivot row to each row.  The multiple factor 
		// is chosen so that the element of A on the pivot column is 0.
		{
			if (irow != iPass) factor = A[n*irow+iPass];
			for (icol = 0; icol < n; icol++)
			{
				if (irow != iPass)
				{
					AInverse[n*irow+icol] -= factor * AInverse[n*iPass+icol];
					A[n*irow+icol] -= factor * A[n*iPass+icol];
				}
			}
		}
	}
	free(ac);
	free(A);
	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// rand functions
///////////////////////////////////////////////////////////////////////////////

//x,mu is column vector
int prob_pdf_gauss_by_vector(double * mu, double * cov, int dim, double * x, double * prob_value)
{
	int ret = 0;
	double   det_sigma;
	
	double * inv_sigma;	//inv(sigma)
	double * x_mu;		//(x-mu)
	double * tr_x_mu;	//tran(x-mu)
	double * tr_x_mu_inv_sigma; //tran(x-mu) * inv(sigma)
	double   tr_x_mu_inv_sigma_x_mu; //tran(x-mu) * inv(sigma) * (x-mu)
	
	double prob = 0;
	*prob_value = 0;	
	
	det_sigma = mat_determinent(cov, dim);

	//compute inverse sigma
	inv_sigma = (double*)calloc(dim*dim, sizeof(double));
	ret = mat_inverse (cov, dim, inv_sigma);
	if(ret == 0)
	{
		return 0;
	}
	
	//compute (x-mu)
	x_mu = (double*)calloc(dim, sizeof(double));
	ret = mat_subtract(x, mu, dim, 1, x_mu); //x must be column vector
	
	//compute tran(x-mu)
	tr_x_mu = (double*)calloc(dim, sizeof(double));
	ret = mat_transpose (x_mu, dim, 1, tr_x_mu);
	
	//compute tran(x-mu)*inv(sigma)
	tr_x_mu_inv_sigma = (double*)calloc(dim, sizeof(double));
	ret = mat_multiply(tr_x_mu, inv_sigma, 1, dim, dim, tr_x_mu_inv_sigma);
	
	//compute tran(x-mu)*inv(sigma)*(x-mu)
	tr_x_mu_inv_sigma_x_mu = 0;
	ret = mat_multiply(tr_x_mu_inv_sigma, x_mu, 1, dim, 1, &tr_x_mu_inv_sigma_x_mu);
	
	prob = sqrt(det_sigma)*exp(-0.5 * tr_x_mu_inv_sigma_x_mu);
	prob = 2.0f * PI * prob;
	*prob_value = prob;
	
	free(inv_sigma);
	free(x_mu);
	free(tr_x_mu);
	free(tr_x_mu_inv_sigma);
	
	return 1;
}


double prob_pdf_gauss(double mu, double sigma, double x)
{
	return (1.0f / sqrt(2.0f*PI*sigma*sigma)) *  exp( -0.5 * ((x-mu)*(x-mu)) / (sigma*sigma));
}

double prob_pdf_gauss_by_one(double mu, double sigma, double multipler, double x)
{
	return (1.0f / sqrt(2.0f*PI*sigma*sigma)) *  exp( -1.0f * multipler * ((x-mu)*(x-mu)) / (sigma*sigma));
}

double prob_pdf_exp(double lambda, double x)
{
	if(x < 0)
	{
		return 0;
	}
	return lambda * exp(-1.0f * lambda * x);
}

double prob_pdf_exp_by_one(double lambda, double multiplier, double x)
{
	if(x < 0)
	{
		return 0;
	}
	return lambda * exp(-1.0f * multiplier * lambda * x);
}

///////////////////////////////////////////////////////////////////////////////
// probability functions
///////////////////////////////////////////////////////////////////////////////
//seed should never be initialized to 0
double rand_uniform(long * seed)
{
	long k = 0;
	if(*seed == 0)
	{
		*seed = 127773;
	}

	k *= *seed/127773;
	*seed=16807*(*seed-k*127773) - 2836*k;
	if(*seed < 0)
	{
		*seed += 2147483647;
	}
	return ((1.0f / 2147483647)*(*seed));
}

double rand_unifrnd(double a, double b, long * seed)
{
	//uniform distributed random numbers between a and b
	double ran = 0;

	ran = rand_uniform(seed);
	return (a+(b-a)*ran);
}

double rand_exprnd(double mu, long *seed)
{
	//generates and exponentially distributed random number with mean equal to 1/mu 
	double x = 0;
	if(mu <= 0)
	{
		return 0;
	}

	do
	{
		x = rand_unifrnd(0.0f, 1.0f, seed);
	}
	while(x == 0);

	return (-log(x)/mu);
}

double rand_gamrnd(int n, double lambda, long * seed)
{
	//generate an n-erlang distributed random no. for parameters
	//(n, lambda); mean = n/lambda
	//using inverse function
	//if n>8, others methods are recommended; see Law and Kelton
	int count = 0;
	double x = 1.0f; //adding exponential random numbers

	for(count = 1; count <= n; count++)
	{
		x = x * rand_uniform(seed);
	}
	x = -log(x);

	return (x/lambda);
}

double rand_gauss(double mean, double std_dev)
{
	return rand_gauss_conf(mean, std_dev, 6.0f);
}

//TODO :: Test the distribution
double rand_gauss_conf(double mean, double std_dev, double conf)
{
	long seed;
	double rand_value = 0;
	double x_value = 0;
	double prob_value = 0;
	
	do
	{
		seed = (long) rand();	
	}while(seed == 0);

	while(1)
	{
		rand_value = rand_unifrnd( 0.0f, 1.0f, &seed);
		x_value	   = rand_unifrnd(-1.0f, 1.0f, &seed) * (std_dev * conf) + mean;
		
		prob_value = prob_pdf_gauss(mean, std_dev, x_value);
		if(prob_value >= rand_value)
		{
			break;
		}
	}
	return x_value;
}

///////////////////////////////////////////////////////////////////////////////
// Markov functions
///////////////////////////////////////////////////////////////////////////////
int markov_nstep_prob(int n, double * a, int dim, double * ret)
{
	int i = 0;
	
	mat_copy(a, ret, dim, dim);
	for( i = 0; i < n; i++)
	{
		mat_multiply(ret, a, dim, dim, dim, ret);
	}
	return 0;
}

int markov_nstep_limit_prob(int n, double * a, int dim, double * limit_prob)
{
	int ret = 0;
	double * tr_prob;
	
	tr_prob = (double*)calloc(dim*dim, sizeof(double));
	ret = markov_nstep_prob(n, a, dim, tr_prob);
	
	ret = markov_limit_prob(tr_prob, dim, limit_prob);
	free(tr_prob);

	return ret;
}

int markov_conv_prob(double * a, int dim, double * ret, double epsilon, int max_iter)
{
	int ret_value = 1;
	int cnt = 0;
	double * tr;
	double * tr_prev;
	double error = 0;


	tr	= (double*)calloc(dim*dim, sizeof(double));
	tr_prev = (double*)calloc(dim*dim, sizeof(double));
	
	mat_copy(a, tr	   , dim, dim);
	mat_copy(a, tr_prev, dim, dim);
	while(1)
	{
		mat_multiply(tr, a, dim, dim, dim, tr);
		cnt++;
		
		error = fabs(mat_abs_diff_max(tr, tr_prev, dim, dim));
		//printf("conv error : %lf\n", error);

		if(error <= epsilon)
		{
			mat_copy(tr, ret, dim, dim);
			ret_value = 0;
			break;
		}

		if(max_iter != -1 && cnt > max_iter)
		{
			ret_value = -1;
			break;
		}
		mat_copy(tr, tr_prev, dim, dim);
	}

	if(0)
	{
		int i, j;
		
		printf("Previous matrix\n");
		for(i = 0; i < dim; i++)
		{
			for(j = 0; j < dim; j++)
			{
				printf("%1.12lf ", tr_prev[i*dim + j]);
			}
			printf("\n");
		}
		printf("Converged matrix\n");
		for(i = 0; i < dim; i++)
		{
			for(j = 0; j < dim; j++)
			{
				printf("%1.12lf ", tr[i*dim + j]);
			}
			printf("\n");
		}
	}
	free(tr_prev);
	free(tr);
	return ret_value;
}
int markov_conv_limit_prob(double * a, int dim, double * limit_prob, double epsilon, int max_iter)
{
	int result = 0;
	double * limit_tr;

	limit_tr = (double*)calloc(dim*dim, sizeof(double));
	if(markov_conv_prob(a, dim, limit_tr, epsilon, max_iter) < 0)
	{
		return -1;
	}
	result = markov_limit_prob(limit_tr, dim, limit_prob);
	
	free(limit_tr);
	return result;
}

int markov_limit_prob(double * a, int dim, double * limit_prob)
{
	int i = 0;
	int ret = 0;

	double * a_inv;
	double * phi_right;
	double * A;
	double * A_tr;
	
	A = (double*)calloc(dim*dim, sizeof(double));
	mat_copy(a, A, dim, dim);

	A_tr = (double*)calloc(dim*dim, sizeof(double));
	mat_transpose(A, dim, dim, A_tr);
	
	// value-1 for diagonal terms
	for(i = 0; i < dim; i++)
	{
		A_tr[i*dim+i] = A_tr[i*dim+i]-1.0f;
	}
	
	// value+1 for last rows
	for(i = 0; i < dim; i++)
	{
		A_tr[dim*(dim-1)+i] = A_tr[dim*(dim-1)+i]+1.0f;
	}

	a_inv = (double*)calloc(dim*dim, sizeof(double));
	ret = mat_inverse (A_tr, dim, a_inv);
	if(ret == 0)
	{
		return 0;
	}

	phi_right = (double*)calloc(dim, sizeof(double));
	for(i = 0; i < dim-1; i++)
	{
		phi_right[i] = 0;
	}
	phi_right[dim-1] = 1.0f;
	
	ret = mat_multiply(a_inv, phi_right, dim, dim, 1, limit_prob);
	
	free(A);
	free(A_tr);
	free(a_inv);
	free(phi_right);
	return 1;
}

int markov_reward(double * reward, double * phi, int dim, double * phi_reward)
{
	return mat_multiply(reward, phi, dim, dim, 1, phi_reward);
}
