#include "Header.h"

int main(int, char**)
{

	char fname[100];

	int count = 0;

	if (!capture.open(ip_address))
	{
		cout << "Cannot connect IP camera! Check Your Camera Connection." << endl;
		system("pause");
		return -1;
	}

	if (!commNumPlate_cascade.load("./cascade/700_cascade.xml"))
	{
		cout << "cascade.load failed!! put the xml file into this project holder\n";
		system("pause");
		return -1;
	}

	for (;;)
	{

		time_t t;

		if (!capture.read(original)) {
			return -1;
		}

		image = original.clone();
		cvtColor(original, gray, CV_BGR2GRAY);

		commNumPlate_cascade.detectMultiScale(gray, commPlate, 1.3, 5);
		for (int i = 0; i < commPlate.size(); i++)
		{

			t = time(NULL);
			Point pt1(commPlate[i].x + commPlate[i].width, commPlate[i].y + commPlate[i].height);
			Point pt2(commPlate[i].x, commPlate[i].y);
			rectangle(image, pt1, pt2, colorNum, 2, 8, 0);
			Mat NumberPlate(original, Rect(pt1, pt2));

			resize(NumberPlate, resizedNP, Size(200, 100), 1.0, 1.0, INTER_LINEAR); //resize(src,dst,size(x,y),x_scale_factor,y_scale_factor,interpolation_type)
			cvtColor(resizedNP, grayNP, CV_BGR2GRAY);

		//	strftime(fname, sizeof(fname), "C:/ImageStorage/commercialNP/commNP_%y%m_%d_%H_%M_%S.png", localtime(&t));
		//	imwrite(fname, grayNP);
		//	count++;
		//	cout << "We got Commercial Number Plate.No." << count << endl;

			Mat binaryNP;
			//blur(grayNP, grayNP, Size(3, 3), Point(-1, -1));
			threshold(grayNP, binaryNP, 0, 255, THRESH_BINARY | THRESH_OTSU);
			Canny(binaryNP, binaryNP, 3, 3);
		//	imshow("binary", binaryNP);
			vector<vector<Point> > contours;
			findContours(binaryNP, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			Mat contoursMat = resizedNP.clone();
			Mat numRect[10];
			int count = 0;

			for (int i = 0; i < contours.size(); i++)
			{
				Rect pointArea = boundingRect(contours[i]);
				double contourRatio = (float)pointArea.width / pointArea.height;
				if (contourRatio > 0.4  && contourRatio < 0.6 && pointArea.height > 30 && pointArea.height < 55) {
					rectangle(contoursMat, pointArea, Scalar(0, 255, 0), 1, 8);
					//Rect numRoi(pointArea.x-2, pointArea.y-2, pointArea.width+2, pointArea.height+2);		
					
					numRect[count] = Mat(resizedNP,pointArea);	
					stringstream nameImgFile;
					nameImgFile << "img/num/left" << count << ".png";
					imwrite(nameImgFile.str(), numRect[count]);
					count++;

				}
			}

			imshow("num0", numRect[0]);
			imshow("contour", contoursMat);
			imshow("captured number", resizedNP);
		}

		imshow("Detecting Number Plate Streaming", image);
		if (waitKey(1) >= 0) break;

	}

	destroyAllWindows;

	return 0;
}

