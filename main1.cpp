#include<iostream>
#include<stdlib.h>
#include <string.h>

using namespace std;

unsigned int W = 0;
unsigned int H = 0;

unsigned char *PGMcols = NULL;
unsigned char **PGMdata = NULL;

typedef struct pix{
  unsigned char r;
  unsigned char g;
  unsigned char b;
}PPMpixel;

PPMpixel *PPMcols = NULL;
PPMpixel **PPMdata = NULL;

char type[2];


bool openPGM(const char* filename);
bool openPPM(const char* filename);
bool savePGM(const char* filename);
bool savePPM(const char* filename);

void threshold(unsigned int th);
void threshold(unsigned int th1, unsigned int th2);


int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    cout << "Error ! Input file must be <exec> <inputfile.pgm/ppm>" << endl;
    return 1;
  }

  FILE* fp = fopen(argv[1], "r");
  if(!fp)
  {
    cout << "Error ! Image must exist!" << endl;
    return 2;
  }
  fscanf(fp, "%s", &type);
  //fscanf(fp, "%c", &type[1]);
  cout << "Image is of type: " << type << endl;
  fclose(fp);
  if(strcmp(type, "P2") == 0)
  {
    if(!openPGM(argv[1]))
    {
      cout << "Error ! Could not load image" << endl;
      return 3;
    }else{
      cout << "Insert a treshold" << endl;
      int th;
      cin >> th;
      threshold(th);
      savePGM("result.pgm");
    }
  }else{
    if(strcmp(type, "P3") == 0)
    {
      if(!openPPM(argv[1]))
      {
        cout << "ERROR ! Could not load image" << endl;
        return 4;
      }else{
        savePPM("result.ppm");
      }
    }else{
      cout << "Error ! Invalid image format" << endl;
    }
  }

  return 0;
}

bool openPGM(const char* filename)
{
  cout << "Loading PGM Image: " << filename << endl;
  FILE* fp = fopen(filename, "r");
  if(!fp)
  {
    return false;
  }

  fseek(fp, 2, SEEK_SET);
  fscanf(fp, "%d %d 255 ", &W, &H);
  cout << "Image Dimensions: \nWidth: " << W << ", Height: " << H << endl;

  PGMdata = (unsigned char**)malloc(H *sizeof(unsigned char**));
  int i;
  int j;
  for(i = 0; i < W; i++)
  {
    PGMcols = (unsigned char*)malloc(W * sizeof(unsigned char*));
    PGMdata[i] = PGMcols;
  }

  for(i = 0; i < H; i++)
  {
    for(j = 0; j < W; j++)
    {
      fscanf(fp, "%d ", &PGMdata[i][j]);
    }
  }

  return true;
}

bool savePGM(const char* filename)
{
   cout << "Saving image : " << filename << endl;
   FILE* fp = fopen(filename, "w");
   if(!fp) return false;

   fprintf(fp, "P2\n");
   fprintf(fp, "%d %d 255\n", W, H);

   for(int i=0; i < H; i++)
   {
     for(int j = 0; j < W; j++)
       fprintf(fp, "%d ", PGMdata[i][j]);
   }
   fclose(fp);

   return true;
}


bool openPPM(const char* filename)
{
  cout << "Loading PPM Image: " << filename << endl;
  FILE* fp = fopen(filename, "r");
  int i;
  int j;

  if(!fp)
  {
    return false;
  }

  fseek(fp, 2, SEEK_SET);
  fscanf(fp, "%d %d 255 ", &W, &H);
  cout << "Image Dimensions: \nWidth: " << W << ", Height: " << H << endl;

  PPMdata = (PPMpixel**)malloc(H*sizeof(PPMpixel**));
  for(i = 0; i < W; i++)
  {
    PPMcols = (PPMpixel*)malloc(W * sizeof(PPMpixel*));
    PPMdata[i] = PPMcols;

  }

  for(i = 0; i < H; i++)
  {
    for(j = 0; j < W; j++)
    {
      fscanf(fp, "%d %d %d ", &PPMdata[i][j].r, &PPMdata[i][j].g, &PPMdata[i][j].b);
    }
  }

  return true;

}

bool savePPM(const char* filename)
{
   cout << "Saving image : " << filename << endl;
   FILE* fp = fopen(filename, "w");
   if(!fp) return false;

   fprintf(fp, "P3\n");
   fprintf(fp, "%d %d 255\n", W, H);

   for(int i=0; i < H; i++)
   {
     for(int j = 0; j < W; j++)
       fprintf(fp, "%d %d %d ", PPMdata[i][j].r, PPMdata[i][j].g, PPMdata[i][j].b);
   }
   fclose(fp);

   return true;
}

void threshold(unsigned int th)
{
  for(int i = 0; i < H; i++)
  {
    for(int j = 0; j < W; j++)
    {
      if(PGMdata[i][j] >= th)
      {
        PGMdata[i][j] = 255;
      }else{
        PGMdata[i][j] = 0;
      }
    }
  }
}

void threshold(unsigned int th1, unsigned int th2)
{

}
