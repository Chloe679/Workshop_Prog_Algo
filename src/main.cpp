#include <sil/sil.hpp>
#include "random.hpp"
void greenImage(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
};



void switchCanal(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y).r, image.pixel(x, y).b);
        }
    }
};

void BlackAndWhite(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float red = image.pixel(x, y).r;
            float blue = image.pixel(x, y).b;
            float green = image.pixel(x, y).g;

            float luminance = 0.2126 * red + 0.7152 * green + 0.0722 * blue; //formule
            image.pixel(x, y).r = luminance;
            image.pixel(x, y).b = luminance;
            image.pixel(x, y).g = luminance;
        }
    }
}





void Negatif(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float red = 1 - image.pixel(x, y).r;
            float blue = 1 - image.pixel(x, y).b;
            float green = 1 - image.pixel(x, y).g;

            image.pixel(x, y).r = red;
            image.pixel(x, y).b = blue;
            image.pixel(x, y).g = green;
        }
    }
}

sil::Image Degrade()
{
    sil::Image image{300, 200}; //on cree une image en noire 
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            float couleur= float(x)/float(image.width() - 1);
            image.pixel(x, y).r = couleur;
            image.pixel(x, y).b = couleur;
            image.pixel(x, y).g = couleur;
        }
    }
    return image;
}

void Miror(sil::Image& image){
    for (int x{0}; x < image.width()/2; x++)
    {

        for (int y{0}; y < image.height(); y++){
            int nvx=(image.width() - (1+x));

            std::swap(image.pixel(nvx, y).r, image.pixel(x, y).r);
            std::swap(image.pixel(nvx, y).b, image.pixel(x, y).b);
            std::swap(image.pixel(nvx, y).g, image.pixel(x, y).g);
        }

}}


void Bruit(sil::Image& image){
 int nbpixel=random_int(1, image.width()*image.height()/2); //nb px bruités
 for (int i{0};i<=nbpixel;i++){
    int x=random_int(0, image.width()-1);
    int y=random_int(0, image.height()-1);
    image.pixel(x,y).r=random_float(0.f,1.f);
    image.pixel(x,y).g=random_float(0.f, 1.f);
    image.pixel(x,y).b=random_float(0.f, 1.f);
 }
}


sil::Image Rotation(sil::Image& image){
    int new_width=image.height();
    int new_height=image.width();
    sil::Image new_image{new_width, new_height}; //nv image 
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(new_width-y-1, x ) = image.pixel(x, y);
        }
    }
    return new_image;
}

sil::Image Split(const sil::Image& image)
{
    sil::Image new_image{image.width(), image.height()};
    int decalage = 50; // pixels de décalage

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
 //pour ne pas déborder
            int xd = x + decalage;
            int xg= x - decalage;
            if (xd >= image.width()) 
                { xd = image.width() - 1;
                }

            if (xg < 0) 
                {xg = 0;
                }
            new_image.pixel(x, y).r = image.pixel(xd, y).r; 
            new_image.pixel(x, y).g = image.pixel(x, y).g;  
            new_image.pixel(x, y).b = image.pixel(xg, y).b; 
        }
    }

    return new_image;
}

void Clair( sil::Image &image){
     for (int x = 0; x < image.width(); x++){
    
        for (int y = 0; y < image.height(); y++)
        {
            auto& p= image.pixel(x,y);
           p.r=pow(p.r,0.2);
            p.g=pow(p.g,0.2);
            p.b=pow(p.b,0.2);
        }
    }
}


void Sombre( sil::Image &image){
     for (int x = 0; x < image.width(); x++){
    
        for (int y = 0; y < image.height(); y++)
        {
            auto& p= image.pixel(x,y);
            p.r=pow(p.r,3);
            p.g=pow(p.g,3);
            p.b=pow(p.b,3);
        }
    }
}
    
sil::Image Disque(){
    sil::Image image{300, 200};
    int rayon=50;
    int Xcentre=image.width()/2;
    int Ycentre=image.height()/2;
    for (int x = 0; x < image.width(); x++){
    
        for (int y = 0; y < image.height(); y++)
        {
            if ( (pow((x-Xcentre),2)+pow((y-Ycentre),2)) < pow(rayon,2)){ //equation cartésienne cercle
                image.pixel(x,y).r=1;
                 image.pixel(x,y).g=1;
                image.pixel(x,y).b=1; //blanc
            }
        }
    }
    return image;
}


sil::Image Cercle(){
    sil::Image image{300, 200};
    int rayon = 50;
    int thickness = 5;
    int Xcentre = image.width() / 2;
    int Ycentre = image.height() / 2;

    for (int x = 0; x < image.width(); x++){
        for (int y = 0; y < image.height(); y++)
        {
            if (
                (pow(x - Xcentre, 2) + pow(y - Ycentre, 2) < pow(rayon, 2)) &&
                (pow(x - Xcentre, 2) + pow(y - Ycentre, 2) > pow(rayon - thickness, 2))
            ) {
                image.pixel(x,y).r = 1;
                image.pixel(x,y).g = 1;
                image.pixel(x,y).b = 1; // blanc
            }
        }
    }
    return image;
}








int main()
{
    {
        sil::Image image{"images/logo.png"};
        greenImage(image);
        image.save("output/greenImage.png");
    }

    {
        sil::Image image{"images/logo.png"};
        switchCanal(image);
        image.save("output/switchCanal.png");
    }

    {
        sil::Image image{"images/logo.png"};
        BlackAndWhite(image);
        image.save("output/BlackAndWhite.png");
    }

    {
        sil::Image image{"images/logo.png"};
        Negatif(image);
        image.save("output/Negatif.png");
    }
    {
        sil::Image image = Degrade();
        image.save("output/Gradient.png");
    }
    {
        sil::Image image{"images/logo.png"};
        Miror(image);
        image.save("output/Miror.png");
    }

    {   sil::Image image{"images/logo.png"};
        Bruit(image);
        image.save("output/Bruit.png");}

        {
       sil::Image image{"images/logo.png"};
        Rotation(image).save("output/Rotation.png");
        }

          {
       sil::Image image{"images/logo.png"};
        Split(image).save("output/Split.png");
        }
        
        {
        sil::Image image{"images/photo.jpg"};
        Clair(image);
        image.save("output/Clair.png");
    }

     {
        sil::Image image{"images/photo.jpg"};
        Sombre(image);
        image.save("output/Sombre.png");
    }

    { sil::Image image=Disque();
        Disque().save("output/Disque.png");
    }

     { sil::Image image=Cercle();
        Cercle().save("output/Cercle.png");
    }
    }