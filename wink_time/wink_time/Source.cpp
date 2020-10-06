#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <windows.h> 

#define _USE_MATH_DEFINES
#include <math.h>

#pragma warning(disable: 4996)

#define ImageWidth  600
#define ImageHeight 600

FILE *eye, *eyep, *headp, *out0, *out1, *out2, *out3, *out4,*out5,*out6;

char readfilename0[] = "eye.csv";
char readfilename1[] = "eyep.csv";
char readfilename2[] = "headp.csv";
char writefilename0[] = "eye_time.csv";
char writefilename1[] = "wink_right.csv";
char writefilename2[] = "wink_left.csv";
char writefilename3[] = "wink.csv";
char writefilename4[] = "no_data.csv";
char writefilename5[] = "eye_data_q.csv";
char writefilename6[] = "eye_data_a.csv";

void main(){

	int no_eye = 0, no_eye_flg = 0, wink_right = 0, wink_left = 0, wink = 0, no_head = 0;
	double no_eye_time[5] = { 0 }, wink_right_time[3] = { 0 }, wink_left_time[3] = { 0 }, wink_time[3] = { 0 }, no_head_time[3] = { 0 };

	char *ary[9];
	double data[7] = { 0 };

	const int buf_size =1028;
	char buf[buf_size];

	eye = fopen(readfilename0, "r");
	eyep = fopen(readfilename1, "r");
	headp = fopen(readfilename2, "r");
	out0 = fopen(writefilename0, "a");
	//out1 = fopen(writefilename1, "a");
	//out2 = fopen(writefilename2, "a");
	out3 = fopen(writefilename3, "a");
	out4 = fopen(writefilename4, "a");
	out5 = fopen(writefilename5, "a");
	out6 = fopen(writefilename6, "a");

	while (fgets(buf, buf_size, eye) != NULL) {

		ary[0] = strtok(buf, ",");
		ary[1] = strtok(NULL, ",");
		ary[2] = strtok(NULL, ",");

		data[0] = atof(ary[0]);
		data[1] = atof(ary[1]);
		data[2] = atof(ary[2]);

		

		if (data[0] <= 790) {

			/*printf("%lf:%lf,%lf\n", data[0], data[1], data[2]);*/



			if (data[1] == -1 && data[2] == -1) {
				if (no_eye == 0) {
					no_eye_time[0] = data[0];
					no_eye = 1;
				}
			}
			else {
				if (no_eye == 1) {
					no_eye = 0;
					no_eye_flg = 1;
				}
			}


			if (no_eye_flg == 1) {

				no_eye_time[1] = data[0];
				no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
				no_eye_flg = 0;

				/*printf("\n\n%lf\n\n", no_eye_time[2]);*/

				fprintf(out0, "%lf,%lf\n", no_eye_time[0], no_eye_time[2]);

			}
		}


	}

	
	Sleep(1000);
	printf("1\n\n");
	fclose(eye);

	while(fgets(buf, buf_size, eyep) != NULL) {

		ary[0] = strtok(buf, ",");
		ary[1] = strtok(NULL, ",");
		ary[2] = strtok(NULL, ",");
		ary[3] = strtok(NULL, ",");
		ary[4] = strtok(NULL, ",");
		ary[5] = strtok(NULL, ",");
		ary[6] = strtok(NULL, ",");
		ary[7] = strtok(NULL, ",");
		ary[8] = strtok(NULL, ",");

		data[0] = atof(ary[0]);
		data[1] = atof(ary[2]);
		data[2] = atof(ary[3]);
		data[3] = atof(ary[4]);
		data[4] = atof(ary[6]);
		data[5] = atof(ary[7]);
		data[6] = atof(ary[8]);

		/*printf("%lf:%lf,%lf,%lf:%lf,%lf,%lf\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6]);*/

		////wink_left
		//if (data[1] == -1) {
		//	if (wink_left == 0) {
		//		wink_left_time[0] = data[0];
		//		wink_left = 1;
		//	}
		//}
		//else {
		//	if (wink_left == 1) {
		//		wink_left_time[1] = data[0];
		//		wink_left_time[2] = wink_left_time[1] - wink_left_time[0];
		//		wink_left = 0;
		//		fprintf(out2, "%lf,%lf,1\n", wink_left_time[0], wink_left_time[2]);
		//	}
		//}

		////wink_right
		//if (data[4] == -1) {
		//	if (wink_right == 0) {
		//		wink_right_time[0] = data[0];
		//		wink_right = 1;
		//	}
		//}
		//else {
		//	if (wink_right == 1) {
		//		wink_right_time[1] = data[0];
		//		wink_right_time[2] = wink_right_time[1] - wink_right_time[0];
		//		wink_right = 0;
		//		fprintf(out1,"%lf,%lf,1\n", wink_right_time[0], wink_right_time[2]);
		//	}
		//}

		//wink
		if (data[1] == -1 && data[4] == -1) {
			if (wink == 0) {
				wink_time[0] = data[0];
				wink = 1;
			}
		}
		else {
			if (wink == 1) {
				wink_time[1] = data[0];
				wink_time[2] = wink_time[1] - wink_time[0];
				wink = 0;
				/*printf( "\n\n%lf,%lf,1\n\n", wink_time[0], wink_time[2]);*/
				fprintf(out3, "%lf,%lf,1\n", wink_time[0], wink_time[2]);
			}
		}


	}

	Sleep(1000);
	printf("2\n\n");
	fclose(eyep);
	


	while (fgets(buf, buf_size, headp) != NULL) {

		ary[0] = strtok(buf, ",");
		ary[1] = strtok(NULL, ",");
		ary[2] = strtok(NULL, ",");
		ary[3] = strtok(NULL, ",");
		ary[4] = strtok(NULL, ",");
		ary[5] = strtok(NULL, ",");
		ary[6] = strtok(NULL, ",");
		ary[7] = strtok(NULL, ",");
		ary[8] = strtok(NULL, ",");

		data[0] = atof(ary[0]);
		data[1] = atof(ary[2]);
		data[2] = atof(ary[3]);
		data[3] = atof(ary[4]);
		data[4] = atof(ary[6]);
		data[5] = atof(ary[7]);
		data[6] = atof(ary[8]);


		//no_head
		if (data[1] == -1 && data[4] == -1) {
			no_head_time[0] = data[0];
			no_head = 1;
			fprintf(out4, "%lf,1\n", no_head_time[0]);
		}


	}

	Sleep(1000);
	printf("3\n\n");
	fclose(headp);


	eye = fopen(readfilename0, "r");

	for (int i = 0; i <= 4; i++) {
		no_eye_time[i] = 0;
	}

	no_eye = 0;
	no_eye_flg = 0;

	int no_eye2 = 0, no_eye_flg2 = 0;

	while (fgets(buf, buf_size, eye) != NULL) {

		ary[0] = strtok(buf, ",");
		ary[1] = strtok(NULL, ",");
		ary[2] = strtok(NULL, ",");

		data[0] = atof(ary[0]);
		data[1] = atof(ary[1]);
		data[2] = atof(ary[2]);





		if (data[0] <= 500) {

			if (190 <= data[0] && data[0] <= 230) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}

			}

			if (230 <= data[0] && data[0] <= 250) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}




			if (250 <= data[0] && data[0] <= 290) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (290 <= data[0] && data[0] <= 310) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}





			if (310 <= data[0] && data[0] <= 350) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (350 <= data[0] && data[0] <= 370) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}








			if (370 <= data[0] && data[0] <= 410) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (410 <= data[0] && data[0] <= 430) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}




			if (430 <= data[0] && data[0] <= 470) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (470 <= data[0] && data[0] <=490) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}




			if (490 <= data[0] && data[0] <= 530) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (530 <= data[0] && data[0] <= 550) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}




			if (550 <= data[0] && data[0] <= 590) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (590 <= data[0] && data[0] <= 610) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}




			if (610 <= data[0] && data[0] <= 650) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (650 <= data[0] && data[0] <= 670) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}




			if (670 <= data[0] && data[0] <= 710) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (710 <= data[0] && data[0] <= 730) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}




			if (730 <= data[0] && data[0] <= 770) {
				fprintf(out5, "%lf,%lf,%lf\n", data[0], data[1], data[2]);
				if (data[1] == -1 && data[2] == -1) {
					if (no_eye == 0) {
						no_eye_time[0] = data[0];
						no_eye = 1;
					}
				}
				else {
					if (no_eye == 1) {
						no_eye = 0;
						no_eye_flg = 1;
					}
				}


				if (no_eye_flg == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg = 0;

					no_eye_time[3] = no_eye_time[3] + no_eye_time[2];

					printf("a:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[3]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}
				}
			}

			if (770<= data[0] && data[0] <= 790) {
				fprintf(out6, "%lf,%lf,%lf\n", data[0], data[1], data[2]);

				if (data[1] == -1 && data[2] == -1) {
					if (no_eye2 == 0) {
						no_eye_time[0] = data[0];
						no_eye2 = 1;
					}
				}
				else {
					if (no_eye2 == 1) {
						no_eye2 = 0;
						no_eye_flg2 = 1;
					}
				}


				if (no_eye_flg2 == 1) {

					no_eye_time[1] = data[0];
					no_eye_time[2] = no_eye_time[1] - no_eye_time[0];
					no_eye_flg2 = 0;

					no_eye_time[4] = no_eye_time[4] + no_eye_time[2];

					printf("bbbbb:%lf--%lf,%lf\n", data[0], no_eye_time[2], no_eye_time[4]);

					if (no_eye_time[2] >= 10) {
						printf("---------\n\n");
					}

				}
			}


		}
		


	}

	fprintf(out5, "\n%lf\n", no_eye_time[3]);

	fprintf(out6, "\n%lf\n", no_eye_time[4]);

	Sleep(1000);
	printf("4\n\n");
	printf("ALL OK\n\n");
	Sleep(5000);

	fclose(eye);

	//fclose(out0);
	//fclose(out1);
	//fclose(out2);
	//fclose(out3);
	//fclose(out4);
	//fclose(out5);
	//fclose(out6);
}