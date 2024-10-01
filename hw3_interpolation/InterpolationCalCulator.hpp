#ifndef ABCD
#define ABCD
#include <opencv2/opencv.hpp>
#endif // !1


enum ColorType {
	Blue ,
	Green,
	Red,
	Gray
};

const double inverse_matrix[16] = { -(1 / 6), 1 / 2,-(1 / 2),1 / 6,1 / 2,-1,1 / 2,0,-(1 / 3),-(1 / 2),1,-(1 / 6),0,1,0,0 };


unsigned char Billinearinterpolation(unsigned char* input, int origin_height, int origin_width, double original_x_point, double original_y_point, int channels,int colorType) {
	
	int mapping_x_point = original_x_point;
	int mapping_y_point = original_y_point;

	int p1_x = mapping_x_point;
	int p1_y = mapping_y_point;

	int p2_x;
	int p2_y;

	int p3_x ;
	int p3_y;

	int p4_x;
	int p4_y;

	double distance_from_left;
	double distance_from_right;

	double distance_from_top;
	double distance_from_bottom;

	double weight_of_p1;
	double weight_of_p2;
	double weight_of_p3;
	double weight_of_p4;
	


		if (mapping_x_point == origin_width - 1 && mapping_y_point == origin_height - 1) { //�ǳ�
			p2_x = mapping_x_point - 1;
			p2_y = mapping_y_point;

			p3_x = mapping_x_point;
			p3_y = mapping_y_point - 1;

			p4_x = mapping_x_point - 1;
			p4_y = mapping_y_point - 1;

			distance_from_right = p1_x-original_x_point;
			distance_from_left = 1 - distance_from_right;

			distance_from_bottom = p1_y-original_y_point;
			distance_from_top = 1 - distance_from_bottom;

			weight_of_p1 = distance_from_right * distance_from_bottom;//(1-a)*b*p1
			weight_of_p2 = distance_from_left * distance_from_bottom;//a*b*p2
			weight_of_p3 = distance_from_right * distance_from_top;//(1-a)*(1-b)*p3
			weight_of_p4 = distance_from_left * distance_from_top;//a*(1-b)*p4

		}
		else if (mapping_x_point == origin_width - 1 && mapping_y_point != origin_height - 1) {//������ �ǳ�(x�࿡�� +1 ��ŭ ������ ������ ������ �� ����)
			p2_x = mapping_x_point - 1;
			p2_y = mapping_y_point;

			p3_x = mapping_x_point;
			p3_y = mapping_y_point + 1;

			p4_x = mapping_x_point - 1;
			p4_y = mapping_y_point + 1;

			distance_from_right = p1_x-original_x_point;
			distance_from_left = 1 - distance_from_right;

			distance_from_top = original_y_point-p1_y;
			distance_from_bottom = 1 - distance_from_top;

			weight_of_p1 = distance_from_right * distance_from_top;//(1-a)*b*p1
			weight_of_p2 = distance_from_left * distance_from_top;//a*b*p2
			weight_of_p3 = distance_from_right * distance_from_bottom;//(1-a)*(1-b)*p3
			weight_of_p4 = distance_from_left * distance_from_bottom;//a*(1-b)*p4

		}
		else if (mapping_x_point != origin_width - 1 && mapping_y_point == origin_height - 1) {//�ǾƷ�(y�࿡�� +1 ��ŭ ������ ������ ������ �� ����)
			p2_x = mapping_x_point + 1;
			p2_y = mapping_y_point;

			p3_x = mapping_x_point;
			p3_y = mapping_y_point - 1;

			p4_x = mapping_x_point + 1;
			p4_y = mapping_y_point - 1;

			distance_from_left = original_x_point-p1_x;
			distance_from_right = 1 - distance_from_left;

			distance_from_bottom = p1_y-original_y_point;
			distance_from_top = 1 - distance_from_bottom;

			weight_of_p1 = distance_from_left * distance_from_bottom;//(1-a)*b*p1
			weight_of_p2 = distance_from_right * distance_from_bottom;//a*b*p2
			weight_of_p3 = distance_from_left * distance_from_top;//(1-a)*(1-b)*p3
			weight_of_p4 = distance_from_right * distance_from_top;//a*(1-b)*p4
		}
		else {//�� �� �Ϲ����� ���

			p2_x = mapping_x_point + 1;
			p2_y = mapping_y_point;

			p3_x = mapping_x_point;
			p3_y = mapping_y_point + 1;

			p4_x = mapping_x_point + 1;
			p4_y = mapping_y_point + 1;

			distance_from_left = original_x_point - p1_x;
			distance_from_right = 1 - distance_from_left;

			distance_from_top = original_y_point - p1_y;
			distance_from_bottom = 1 - distance_from_top;

			weight_of_p1 = distance_from_left * distance_from_top;//(1-a)*b*p1
			weight_of_p2 = distance_from_right * distance_from_top;//a*b*p2
			weight_of_p3 = distance_from_left * distance_from_bottom;//(1-a)*(1-b)*p3
			weight_of_p4 = distance_from_right * distance_from_bottom;//a*(1-b)*p4
		}

		if (channels == 3) {
			return weight_of_p1 * input[(3 * (p1_y * origin_width + p1_x)) + colorType] + weight_of_p2 * input[(3 * (p2_y * origin_width + p2_x)) + colorType] + weight_of_p3 * input[(3 * (p3_y * origin_width + p3_x)) + colorType] + weight_of_p4 * input[(3 * (p4_y * origin_width + p4_x)) + colorType];
		}
		else {
			return (weight_of_p1 * input[p1_y * origin_width + p1_x] + weight_of_p2 * input[p2_y * origin_width + p2_x] + weight_of_p3 * input[p3_y * origin_width + p3_x] + weight_of_p4 * input[p4_y * origin_width + p4_x]);
		}
		

}



unsigned char Bicubicinterpolation(unsigned char* input, int origin_height, int origin_width, double mapping_x_point, double mapping_y_point, int channels,int colorType) {
	//���� 0�ٺ��� 3�ٱ�����. ��, ������ġ +3 ���� �� ������ �־���Ѵ�.
	

	int pM1_x;
	int p0_x;
	int p1_x;
	int p2_x;
	
	int row1_y;
	int row2_y;
	int row3_y;
	int row4_y;
	

	double power_of_standard_point[4];
	double power_of_standard_y_point[4];
	
		if (mapping_x_point - 1 < 0) { //���ʿ� �ƹ� �ȼ��� ���� ���
			p0_x = mapping_x_point + 1;
			pM1_x = p0_x - 1;
			p1_x = p0_x + 1;
			p2_x = p0_x + 2;
			if (mapping_y_point + 1 == origin_height - 1) {//�Ʒ��� ĭ�� �� ĭ�� �ִ� ���
				//�� ���, p1���� �������� �ű��.
				//��, ������ �� ĭ ���� ���ܼ� �����
				row2_y = mapping_y_point - 1;
				row1_y = row2_y-1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;

			}
			else if (mapping_y_point == origin_height - 1) {//�Ʒ��� ĭ�� ���� ���
				//�� ���, p1���� �������� �ű��
				//��, ������ �� ĭ ���� ���ܼ� �����.
				row2_y = mapping_y_point - 2;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;

			}
			else if (mapping_y_point == 0) {//���� ĭ�� ���� ���
				//�� ���, p1���� �������� �ű��.
				//��, ������ �� ĭ �Ʒ��� ���ܼ� �����.
				row2_y = mapping_y_point +1;
				row1_y = row2_y -1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;
			}
			else {//���ʿ� �ƹ� �ȼ��� ���� ��츸 ó��
				//�� ���, p1���� �������� �ű��.
				row2_y = mapping_y_point;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;
			}

		}
		else if (mapping_x_point + 1 == origin_width - 1) {//���������� �� ��° ĭ�� �ȼ��� ���� ���
			p0_x = mapping_x_point -1;
			pM1_x = p0_x - 1;
			p1_x = p0_x + 1;
			p2_x = p0_x + 2;
			if (mapping_y_point + 1 == origin_height - 1) {//�Ʒ��� ĭ�� �� ĭ�� �ִ� ���
				//�� ���, pM1�� �������� �ű��.
				//��, ������ �� ĭ ���� ���ܼ� �����.
				row2_y = mapping_y_point - 1;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;
			}
			else if (mapping_y_point == origin_height - 1) {//�Ʒ��� ĭ�� ���� ���
				//�� ���, pM1�� �������� �ű��.
				//��, ������ �� ĭ ���� ���ܼ� �����.
				row2_y = mapping_y_point - 2;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;
			}
			else if (mapping_y_point == 0) {//���� ĭ�� ���� ���
				//�� ���, pM1�� �������� �ű��.
				//��, ������ �Ʒ��� �ϳ� ���ܼ� �����.
				row2_y = mapping_y_point +1;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;
			}
			else {//���������� �� ��° ĭ�� �ȼ��� ���� ��츸 ó��
				//�� ���, pM1�� �������� �ű��.
				row2_y = mapping_y_point;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;

			}

		}
		else if (mapping_x_point == origin_width - 1) {//�����ʿ� �ƹ� �ȼ��� ���� ���
			p0_x = mapping_x_point - 2;
			pM1_x = p0_x - 1;
			p1_x = p0_x + 1;
			p2_x = p0_x + 2;
			if (mapping_y_point + 1 == origin_height - 1) {//�Ʒ��� ĭ�� �� ĭ�� �ִ� ���
				//�� ���, pM1�� �������� �ű��.
				//��, ������ �� ĭ ���� ���ܼ� �����.
				row2_y = mapping_y_point - 1;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;
			}
			else if (mapping_y_point == origin_height - 1) {//�Ʒ��� ĭ�� ���� ���
				//�� ���, pM1�� �������� �ű��.
				//��, ������ �� ĭ ���� ���ܼ� �����.
				row2_y = mapping_y_point - 2;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;
			}
			else if (mapping_y_point == 0) {//���� ĭ�� ���� ���
				//�� ���, pM1�� �������� �ű��.
				//��, ������ �Ʒ��� �ϳ� ���ܼ� �����.
				row2_y = mapping_y_point + 1;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;
			}
			else {//���������� �� ��° ĭ�� �ȼ��� ���� ��츸 ó��
				//�� ���, pM1�� �������� �ű��.
				row2_y = mapping_y_point;
				row1_y = row2_y - 1;
				row3_y = row2_y + 1;
				row4_y = row2_y + 2;

			}
		}
		else if (mapping_y_point == 0) {//���� �����ʿ��� ������ ������ ���δ� ĭ�� �ϳ��� ����
			//������ �� ĭ �Ʒ��� �ű�⸸ �Ѵ�.
			p0_x = mapping_x_point;
			pM1_x = p0_x - 1;
			p1_x = p0_x + 1;
			p2_x = p0_x + 2;
			row2_y = mapping_y_point +1;
			row1_y = row2_y - 1;
			row3_y = row2_y + 2;
			row4_y = row2_y + 3;
		}
		else if (mapping_y_point + 1 == origin_height - 1) {//�Ʒ��� ĭ�� �� �ϳ� ���� ��
			//������ �� ĭ ���� �ű�⸸ �Ѵ�.
			p0_x = mapping_x_point;
			pM1_x = p0_x - 1;
			p1_x = p0_x + 1;
			p2_x = p0_x + 2;
			row2_y = mapping_y_point - 1;
			row1_y = row2_y - 1;
			row3_y = row2_y + 1;
			row4_y = row2_y + 2;
		}
		else if (mapping_y_point == origin_height - 1) {//�Ʒ��� ĭ�� ����  ��
			//������ �� ĭ ���� �ű�⸸ �Ѵ�.
			p0_x = mapping_x_point;
			pM1_x = p0_x - 1;
			p1_x = p0_x + 1;
			p2_x = p0_x + 2;
			row2_y = mapping_y_point-2;
			row1_y = row2_y - 1;
			row3_y = row2_y + 1;
			row4_y = row2_y + 2;
		}
		else {//�� �� �Ϲ����� ���
			p0_x = mapping_x_point;
			pM1_x = p0_x - 1;
			p1_x = p0_x + 1;
			p2_x = p0_x + 2;
			row2_y = mapping_y_point;
			row1_y = row2_y - 1;
			row3_y = row2_y + 1;
			row4_y = row2_y + 2;

		}


		double normalized_x = (mapping_x_point >= p0_x) ? (mapping_x_point - p0_x ): (p0_x - mapping_x_point);
		double normalized_y = (mapping_y_point >= row2_y) ? (mapping_y_point - row2_y) : (row2_y- mapping_x_point);
		for (int i = 3; i >= 0; i--) {
			power_of_standard_point[i] = pow(normalized_x, i);
		}
		for (int i = 3; i >= 0; i--) {
			power_of_standard_y_point[i] = pow(normalized_y, i);
		}

		double common_vector[4] = { 0,0,0,0 };

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				common_vector[i] += inverse_matrix[(j*4)+i] * power_of_standard_point[3-j];
			}
		}

		double y_common_vector[4] = { 0,0,0,0 };

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				y_common_vector[i] += inverse_matrix[(j * 4) + i] * power_of_standard_y_point[3-j];
			}
		}

		if (channels == 3) {
			int row1_fM1 = input[(int)(3*(row1_y * origin_width + pM1_x)+colorType)];
			int row1_f0 = input[(int)(3*(row1_y * origin_width + p0_x)+colorType)];
			int row1_f1 = input[(int)(3*(row1_y * origin_width + p1_x)+colorType)];
			int row1_f2 = input[(int)(3*(row1_y * origin_width + p2_x)+colorType)];
			double row1_result = (row1_fM1* common_vector[0] + row1_f0 * common_vector[1] + row1_f1 * common_vector[2] + row1_f2 * common_vector[3]);

			int row2_fM1 = input[(int)(3 * (row2_y * origin_width + pM1_x) + colorType)];
			int row2_f0 = input[(int)(3 * (row2_y * origin_width + p0_x) + colorType)];
			int row2_f1 = input[(int)(3 * (row2_y * origin_width + p1_x) + colorType)];
			int row2_f2 = input[(int)(3 * (row2_y * origin_width + p2_x) + colorType)];
			double row2_result = (row2_fM1 * common_vector[0] + row2_f0 * common_vector[1] + row2_f1 * common_vector[2] + row2_f2 * common_vector[3]);

			int row3_fM1 = input[(int)(3 * (row3_y * origin_width + pM1_x) + colorType)];
			int row3_f0 = input[(int)(3 * (row3_y * origin_width + p0_x) + colorType)];
			int row3_f1 = input[(int)(3 * (row3_y * origin_width + p1_x) + colorType)];
			int row3_f2 = input[(int)(3 * (row3_y * origin_width + p2_x) + colorType)];
			double row3_result = (row3_fM1 * common_vector[0] + row3_f0 * common_vector[1] + row3_f1 * common_vector[2] + row3_f2 * common_vector[3]);

			int row4_fM1 = input[(int)(3 * (row4_y * origin_width + pM1_x) + colorType)];
			int row4_f0 = input[(int)(3 * (row4_y * origin_width + p0_x) + colorType)];
			int row4_f1 = input[(int)(3 * (row4_y * origin_width + p1_x) + colorType)];
			int row4_f2 = input[(int)(3 * (row4_y * origin_width + p2_x) + colorType)];
			double row4_result =  (row4_fM1 * common_vector[0] + row4_f0 * common_vector[1] + row4_f1 * common_vector[2] + row4_f2 * common_vector[3]);


			double final_result = row1_result * y_common_vector[0] + row2_result * y_common_vector[1] + row3_result * y_common_vector[2] + row4_result * y_common_vector[3];

			return std::max(0,std::min(255,(int)(final_result)));
		}
		else {
			int row1_fM1=input[(int)(row1_y*origin_width+pM1_x)];
			int row1_f0 = input[(int)(row1_y * origin_width + p0_x)];
			int row1_f1 = input[(int)(row1_y * origin_width + p1_x)];
			int row1_f2 = input[(int)(row1_y * origin_width + p2_x)];
			double row1_result =(row1_fM1 * common_vector[0] + row1_f0 * common_vector[1] + row1_f1 * common_vector[2] + row1_f2 * common_vector[3]);

			int row2_fM1 = input[(int)(row2_y * origin_width + pM1_x)];
			int row2_f0 = input[(int)(row2_y * origin_width + p0_x)];
			int row2_f1 = input[(int)(row2_y * origin_width + p1_x)];
			int row2_f2 = input[(int)(row2_y * origin_width + p2_x)];
			double row2_result = (row2_fM1 * common_vector[0] + row2_f0 * common_vector[1] + row2_f1 * common_vector[2] + row2_f2 * common_vector[3]);

			int row3_fM1 = input[(int)(row3_y * origin_width + pM1_x)];
			int row3_f0 = input[(int)(row3_y * origin_width + p0_x)];
			int row3_f1 = input[(int)(row3_y * origin_width + p1_x)];
			int row3_f2 = input[(int)(row3_y * origin_width + p2_x)];
			double row3_result = (row3_fM1 * common_vector[0] + row3_f0 * common_vector[1] + row3_f1 * common_vector[2] + row3_f2 * common_vector[3]);

			int row4_fM1 = input[(int)(row4_y * origin_width + pM1_x)];
			int row4_f0 = input[(int)(row4_y * origin_width + p0_x)];
			int row4_f1 = input[(int)(row4_y * origin_width + p1_x)];
			int row4_f2 = input[(int)(row4_y * origin_width + p2_x)];
			double row4_result =(row4_fM1 * common_vector[0] + row4_f0 * common_vector[1] + row4_f1 * common_vector[2] + row4_f2 * common_vector[3]);


			double final_result = row1_result * y_common_vector[0] + row2_result * y_common_vector[1] + row3_result * y_common_vector[2] + row4_result * y_common_vector[3];

			return std::max(0, std::min(255, (int)(final_result)));
		}
		
	}