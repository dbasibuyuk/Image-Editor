#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <string>




using namespace std;

class ImageEditor
{  
    private:
        int* pixels;
        int length;
        int nextIndex;

        int columns;
        int rows;
        int maxColor; // 255
        int loaded;
    
        string imageName; 
        string format;
    public:
        ImageEditor(); // constructor
        ~ImageEditor(); // destructor
        //ImageEditor(const ImageEditor& image); // copy constructor when i use it, it crashes the code..
        void operator = (const ImageEditor& rightImage);
        ImageEditor operator + (ImageEditor& rightImage);

        void add(int val);
        void print();
        void saveImage();
        int size();
        int readImage();
        int gScaleConvert();
        string getName();
        int getLength();
        int getLoaded();
        void setName(string str);
        void setLoaded(int loadd);
    
};

int menu(ImageEditor image1, ImageEditor image2, ImageEditor image3);
void imageNames(ImageEditor image1, ImageEditor image2, ImageEditor image3);

int main()
{
    ImageEditor image1, image2, image3;
    menu(image1, image2, image3);
    return 0;
}


void ImageEditor::add(int val) 
{
    int* newArray;
    if(nextIndex == length)
    {
        length += 1;
        newArray = new int[length];

        for(int i = 0; i < nextIndex; i++)
        {
            newArray[i] = pixels[i];
        }

        delete [] pixels;
        pixels = newArray;
    }

    pixels[nextIndex] = val;
    nextIndex++;
}
void ImageEditor::print()
{
    for(int i = 0; i < nextIndex; i++)
    {
        cout << pixels[i] << endl;
    }
}

ImageEditor::ImageEditor()
    {
        maxColor = 255;
        pixels = new int[3];
        nextIndex = 0;
        length = 3;
        imageName = "Not loaded yet\n";
        loaded = 0;
    }


ImageEditor::~ImageEditor()
    {
        delete[] pixels;
    }


int ImageEditor::size() 
{
    return length;
}


int ImageEditor::readImage()
{
    fstream myFile;

    string tempStr;
    int flag = 0; // when it is 4, it means we are done with header part. (format, maxColor, rows and columns)
    
    cin >>  imageName;

    myFile.open(imageName);
    if(myFile.is_open())
    {
        /* header part */
        while(flag < 4)
        {
            myFile >> tempStr;
            if(flag < 4)
            {
                if(tempStr[0] == 'P')
                {
                    format = "P3";
                    flag++;
                }
                // comment, so we ignore them.
                else if(tempStr[0] == '#')
                {
                    getline(myFile, tempStr);
                }

                else
                {
                    if(flag == 1)
                    {
                        columns = stoi(tempStr);
                        flag++;
                    }
                    // it is rows
                    else if(flag == 2)
                    {
                        rows = stoi(tempStr);
                        flag++;
                    }
                    else if(flag == 3)
                    {
                        maxColor = stoi(tempStr);
                        flag++;
                    }
                }
            }
        }

        /* pixel part */
        while(!myFile.eof())
        {
            int value;
            myFile >> value;
            add(value);
        }
        loaded = 1;
        myFile.close();
        return 0;
    }
    // fail to read
    else
    {
        cout << "reading fault";
        return -1;
    }
}


int ImageEditor::gScaleConvert()
{

    // to be whitespace immune, until sscanf
    char inputs[50], c;
    string temp;
    double c_r, c_g, c_b;
    double t_c_r, t_c_g, t_c_b;
    cin >> c;
    getline(cin, temp);

    int i = 0;
    while(temp[i] != '\0')
    {
        inputs[i] = temp[i];
        i++;
    }
    inputs[i] = '\0';  

    sscanf(inputs, "%lf %lf %lf", &t_c_r, &t_c_g, &t_c_b);
    cout << "coefficents  " << t_c_r << " " << t_c_g << " " << t_c_b << endl;

    // if it is  in the range
    if(t_c_r >= 0 && t_c_r < 1)
    {
        c_r = t_c_r;
    }
    else
    {
        return -1;
    }

    if(t_c_g >= 0 && t_c_g < 1)
    {
        c_g = t_c_g;
    }
    else
    {
        return -1;
    }

    if(t_c_b >= 0 && t_c_b < 1)
    {
        c_b = t_c_b;
    }
    else
    {
        return -1;
    }

    int grayscale ;

    for(int i = 0; i < nextIndex; i += 3)
    {
        grayscale = 0;
        grayscale = (c_r * pixels[i]) + (c_g * pixels[i]) + (c_b * pixels[i]);

        if(grayscale > 255)
        {
            pixels[i] = 255;
            pixels[i + 1] = 255;
            pixels[i + 2] = 255;
        }
        else
        {
            pixels[i] = grayscale;
            pixels[i + 1] = grayscale;
            pixels[i + 2] = grayscale;
        }
    }
    return 0;
}




int menu(ImageEditor image1, ImageEditor image2, ImageEditor image3)
{
    int flag = 0, returnCheck;
    int opt1, opt1_1, opt2, opt2_1, opt3, opt3_1, opt3_2;
    string name;
    do
    {
        cout << "MAIN MENU" << endl;
        cout << "0 - Exit" << endl;
        cout << "1 - Open Images(D)" << endl;
        cout << "2 - Save Image Data(D)" << endl;
        cout << "3 - Scripts(D)" << endl;
        cin >> flag;

        // exit
        if(flag == 0)
        {  
            return 0;
        }

        // open an image
        while(flag == 1)
        {
            cout << "OPEN AN IMAGE MENU" << endl;
            cout << "0 - UP" << endl;
            cout << "1 - Open 1 Image" << endl;
            cout << "2 - Open 2 Images" << endl;

            cin >> opt1;
            if(opt1 == 0)
            {
                flag = 0;
            }
            else if(opt1 == 1)
            {  
                opt1_1 = 1;
            
                while(opt1_1 == 1)
                {
                    cout << "0 - UP" << endl;
                    cout << "1 - Enter The Name Of The Image File" << endl;
                    cin >> opt1_1;

                    if(opt1_1 == 0)
                    {
                        opt1_1 = 0;
                    }
                    else if(opt1_1 == 1)
                    {
                        returnCheck = image1.readImage();
                        if(returnCheck == -1)
                        {
                            return 0;
                        }
                    }
                    else if(opt1_1 == 2)
                    {
                        returnCheck = image2.readImage();
                        if(returnCheck == -1)
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        return 0;
                    }
                }

            }
            else if(opt1 == 2)
            {
                opt1_1 = 1;
            
                while(opt1_1 == 1)
                {
                    cout << "0 - UP" << endl;
                    cout << "1 - Enter The Name Of The First Image File" << endl;
                    cout << "2 - Enter The Name Of The Second Image File" << endl;
                    cin >> opt1_1;

                    if(opt1_1 == 0)
                    {
                        opt1_1 = 0;
                    }
                    else if(opt1_1 == 1)
                    {
                        returnCheck = image1.readImage();
                        if(returnCheck == -1)
                        {
                            return 0;
                        }
                    }
                    else if(opt1_1 == 2)
                    {
                        returnCheck = image2.readImage();
                        if(returnCheck == -1)
                        {
                            return 0;
                        }
                        opt1_1 = 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                
            }
            else
            {
                return 0;
            }
        }
            
        // save image data 
        while(flag == 2)
        {
            cout << "SAVE IMAGE DATA MENU" << endl;
            cout << "0 - UP" << endl;
            cout << "1 - Choose The File" << endl;

            cin >> opt2;
            if(opt2 == 0)
            {
                flag = 0;
            }
            else if(opt2 == 1)
            {
                opt2_1 = 1;
                while(opt2_1 == 1)
                {

                    imageNames(image1, image2, image3);

                    cin >> opt2_1;


                    if(opt2_1 == 1)
                    {
                        if(image1.getLoaded() == 1)
                        {
                            image1.saveImage();
                        }
                        else
                        {

                        }
                        opt2_1 = 0;
                    }
                    else if(opt2_1 == 2)
                    {  
                        if(image2.getLoaded() == 1)
                        {
                            image2.saveImage();
                        }

                        opt2_1 = 0;
                    }
                    else if(opt2_1 == 3)
                    {
                        if(image3.getLoaded() == 1)
                        {
                            image3.saveImage();
                        }
                        opt2_1 = 0;
                    }
                    else if(opt2_1 == 0)
                    {
                        opt2_1 = 0;
                    }
                    else
                    {
                        return 0;
                    }
                }                
            }
            else
            {
                return 0;
            }
        }

        // scripts
        while(flag == 3)
        {
            cout << "SCRIPTS MENU" << endl;
            cout << "0 - UP" << endl;
            cout << "1 - Convert To Grayscale(D)" << endl;
            cout << "2 - Sums Two Images" << endl;

            cin >> opt3;
            if(opt3 == 0)
            {
                flag = 0;
            }
            else if(opt3 == 1)
            {
                opt3_1 = 1;
                while(opt3_1 == 1)
                {
                    char temp;
                    cout << "CONVERT TO GRAYSCALE MENU" << endl;
                    cout << "0 - UP" << endl;
                    imageNames(image1, image2, image3);

                    
                    
                    cin >> opt3_1;
                    if(opt3_1 == 0)
                    {
                        opt3_1 = 0;
                        opt3 = 2;
                    }
                    else if(opt3_1 == 1)
                    {
                        opt3_2 = 1;
                        while(opt3_2 == 1)
                        {
                            cout << "0 - UP" << endl;
                            cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;

                            cin >> opt3_2;
                            if(opt3_2 == 0)
                            {
                                opt3_2 = 0;
                                opt3_1 = 0;
                            }

                            else if(opt3_2 == 1)
                            {
                                returnCheck = image1.gScaleConvert();
                                if(returnCheck == -1)
                                {
                                    return 0;
                                }
                            }
                            else
                            {
                                return 0;
                            }
                        }
                    
                    }
                    else if(opt3_1 == 2)
                    {
                        opt3_2 = 1;
                        while(opt3_2 == 1)
                        {
                            cout << "0 - UP" << endl;
                            cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;
                            cin >> opt3_2;
                            if(opt3_2 == 0)
                            {
                                opt3_2 = 0;
                            }
                            else if(opt3_2 == 1)
                            {
                                returnCheck = image2.gScaleConvert();
                                if(returnCheck == -1)
                                {
                                    return 0;
                                }
                            }
                            else
                            {
                                return 0;
                            }
                        }
                    }
                    else if(opt3_1 == 3)
                    {
                        opt3_2 = 1;
                        while(opt3_2 == 1)
                        {
                            cout << "0 - UP" << endl;
                            cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;

                            cin >> opt3_2;

                            if(opt3_2 == 0)
                            {
                                opt3_2 = 0;
                            }
                            else if(opt3_2 == 1)
                            {
                                returnCheck = image2.gScaleConvert();
                                if(returnCheck == -1)
                                {
                                    return 0;
                                }
                            }
                            else
                            {
                                return 0;
                            }
                        }
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
            else if(opt3 == 2)
            {
                image3 = image1 + image2;
                image3.setLoaded(1);
            }
            else
            {
                return 0;
            }
        }


    } while (flag == 0);

    return 0;
}

void ImageEditor::operator = (const ImageEditor& rightImage)
{
    length = rightImage.length;
    nextIndex = rightImage.nextIndex;
    columns = rightImage.columns;
    rows = rightImage.rows;
    maxColor = rightImage.maxColor;
    imageName = rightImage.imageName;
    string format = "P3";

    for(int i = 0; i <rightImage.nextIndex; i++)
    {
        pixels[i] = rightImage.pixels[i];
    }
}

ImageEditor ImageEditor::operator + (ImageEditor& rightImage)
{
    ImageEditor resultImage;
    resultImage.maxColor = 255;
    resultImage.length = rightImage.length;
    resultImage.nextIndex = rightImage.nextIndex;
    resultImage.columns = rightImage.columns;
    resultImage.rows = rightImage.rows;
    string imageName = "newImage";
    string format = "P3";

    for(int i = 0; i < rightImage.nextIndex; i++)
    {
        int temp = 0;
        temp = pixels[i] + rightImage.pixels[i];
        if(temp > 255)
        {
            resultImage.pixels[i] = 255;
        }
        else
        {
            resultImage.pixels[i] = temp;
        }
    }

    return resultImage;
}

void imageNames(ImageEditor image1, ImageEditor image2, ImageEditor image3)
{
    int decision;
    int i = 1;
    if(image1.getLength() > 2)
    {
        cout << i << " - " << image1.getName() << endl;
        i++;
    }
    if(image2.getLength() > 2)
    {

        cout << i << " - " << image2.getName() << endl;
        i++;
    }
    if(image3.getLength() > 2)
    {
        cout << i << " - " << image3.getName() << endl;
        i++;
    }
}


string ImageEditor::getName()
{
    return imageName;
}

int ImageEditor::getLength()
{
    return length;
}

void ImageEditor::saveImage()
{
    char temp;
    string outputName;
    // prints to the destination file
    
    cout << "Enter an output name" << endl;
    getline(cin, outputName);

    fstream myFile;

    myFile.open(outputName, ios::out);

    myFile << "P3" << endl;
    myFile << columns << endl << rows << endl;
    myFile << maxColor << endl;

    for(int i = 0; i < nextIndex; i += 3)
    {
        myFile << pixels[i] << endl << pixels[i + 1] << endl << pixels[i + 2] << endl;
    }
    
    myFile.close();
}


int ImageEditor::getLoaded()
{
    return loaded;
}

/*

ImageEditor::ImageEditor(const ImageEditor& image)
{  
    length = image.length;
    nextIndex = image.nextIndex;
    columns = image.columns;
    rows = image.rows;
    maxColor = image.maxColor;
    imageName = image.imageName;
    format = image.format;

    for(int i = 0; i <image.nextIndex; i++)
    {
        pixels[i] = image.pixels[i];
    }
}
*/
void ImageEditor::setName(string str)
{
    imageName = str;
}
void ImageEditor::setLoaded(int loadd)
{
    loaded = loadd;
}