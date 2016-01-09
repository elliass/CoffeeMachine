/*************************************************************************************************/
/*@note
	�@���ļ��ﶨ�x�����е�ĳɆT���� 
*/

/**includes***************************************************************************************/ 
#include "auxiliary.h"
#include "class_dec.h"

/**CS::Fuctions***********************************************************************************/

/*@note
	CS�Ę��캯�� 
*/
CS::CS()
	{
		strcpy(name,"TCS");
		x=0;
		y=0;
		angle=0;
	}

/*@note
	�Á��O���½�����ϵ�������������ϵ��ƽ�ơ����D��
*/	
void CS::Set(char n[11],float a,float b,float c)
	{
		strcpy(name,n);
		x=a;
		y=b;
		angle=c;
	}

/*@note
	�@ȡ����ϵ���Q
*/	
char* CS::GetName()
	{
		return name;
	}

/*@note
	����ԓ����ϵ���Ñ�Ҫ��C���˵��_������
*/	
void CS::Insert(float a,float b)
	{
		para1=a;
		para2=b;
	}	

/*@note
	��ԓ����ϵ�µ�����׃�Q����������ϵ�������P������ϵ�е�����ֵ
*/ 
void CS::Transform()
{
		/*MatrixXd mov(3,3);
		mov(0,0)=cos(angle*0.0174533);
		mov(0,1)=sin(angle*0.0174533);
		mov(0,2)=x;
		mov(1,0)=-sin(angle*0.0174533);
		mov(1,1)=cos(angle*0.0174533);
		mov(1,2)=y;
		mov(2,0)=0;
		mov(2,1)=0;
		mov(2,2)=1;
		MatrixXd coor_TCS(3,1);
		coor_TCS(0,0)=para1;
		coor_TCS(1,0)=para2;
		coor_TCS(2,0)=1;
		MatrixXd coor_WCS(3,1);
		coor_WCS=mov*coor_TCS;*/
		
	float w_para1;
	float w_para2;
	w_para1=para1*cos(angle*0.0174533)+para2*sin(angle*0.0174533);
	w_para2=-para1*sin(angle*0.0174533)+para2*cos(angle*0.0174533);
	
	if((w_para1*w_para1+w_para2*w_para2)>400)    //�@�e�ٶ��C���˃ɂ��ֱ۵��L�ȶ���10�����԰돽20�ĈA����ĵط��ǵ����˵� 
	{
		cout<<"Robot can't reach that point!"<<endl;
		robot.Set(90,180);
	}
	else
	{
		cout<<"The coordinates of the Robot in WCS are shown as below:"<<endl<<"("<<w_para1<<","<<w_para2<<")"<<endl;
		robot.Set((acos(sqrt(w_para1*w_para1+w_para2*w_para2)/20)+atan(w_para2/w_para1))*57.29578,\
			(2*(1.5707963-acos(sqrt(w_para1*w_para1+w_para2*w_para2)/20)))*57.29578);
	}
}

/**myRobot::Functions*****************************************************************************/

/*@note
	���캯��
*/ 
myRobot::myRobot()
	{
		angle1=90;
		angle2=180;
		CS* p;
		p=new CS;
		char str[4]={'W','C','S','\0'};
		p->Set(str,0,0,0);
		cs_vector.push_back(*p);
	}
	
/*@note
	�����P������ϵ�µ�����ֵ
*/	
void myRobot::Set(float a,float b)
	{
		angle1=a;
		angle2=b;
	}

/*@note
	�Д��Ñ����½�����ϵ߀���ƄәC����
*/	
void myRobot::Operation()
	{
		
		if(strcmp(input.OperationType,"S")==0)
			{
				CS* p;
				p=new CS;
				p->Set(input.CSName,input.para1,input.para2,input.para3);
				cs_vector.push_back(*p);
			}
		else
			{
				PTPMove();
			}		
	}

/*@note
	���F����׃�Q�������P������ϵ������
*/ 
void myRobot::PTPMove()
	{
		for(it=cs_vector.begin();it!=cs_vector.end();it++)
			{
				if(strcmp(it->GetName(),input.CSName)==0)
					{
						it->Insert(input.para1,input.para2);
						it->Transform();
						Show();
						break;
					}
			}
	}

/*@note
	�@ʾ�P������ϵ������
*/	
void myRobot::Show()
	{
		cout<<"The coordinates of the Robot in Joint_CS are shown as below:"<<endl<<"("<<angle1<<","<<angle2<<")"<<endl;
	}
	
