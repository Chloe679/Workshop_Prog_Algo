#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include<complex>
#include <glm/gtx/matrix_transform_2d.hpp>
#include<vector> 



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




sil::Image Rosace(){
        sil::Image image{300, 300};
        int rayon = 50;
        float teta=0;
        int thickness = 3;
    for (int nb=0; nb<6;nb++){
        teta= 3.14 *2*nb/6;
        int Xcentre = image.width()/2+rayon*cos(teta);
        int Ycentre = image.height()/2+rayon*sin(teta);

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
         Xcentre = image.width() / 2;
         Ycentre = image.height() / 2;

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
    }
        return image;
}


sil::Image Mosaique(sil::Image& image){ 
    sil::Image newimage{1000, 1000}; //augmenetr car on voit pas
    int sourcex;
    int sourcey;
     for (int x{0}; x < newimage.width(); x++)
    {
        for (int y{0}; y < newimage.height(); y++)
        {
            sourcex=x%image.width();
            sourcey=y%image.height();
            newimage.pixel(x,y)= image.pixel(sourcex,sourcey);
        }
    }
return newimage;
}


sil::Image MosaiqueMiroir(sil::Image& image){ 
    sil::Image newimage{1000, 1000}; //augmenetr car on voit pas
    int sourcex;
    int sourcey;
    
    int miroir=0;
     for (int x{0}; x < newimage.width(); x++)
    {
        for (int y{0}; y < newimage.height(); y++)
        {
            int indX=x/image.width();
            int indY=y/image.height();
            if((indX%2==0)&&(indY%2==0)){ //aucun miroir
            
                sourcex=x%image.width();
                sourcey=y%image.height();
                newimage.pixel(x,y)= image.pixel(sourcex,sourcey);
            }
            else if ((indX%2==0)&&(indY%2==1)){ //inverse horizon
                sourcex=x%image.width();
                sourcey=image.height()-1-y%image.height();
                newimage.pixel(x,y)= image.pixel(sourcex,sourcey);
            }
            else if ((indX%2==1)&&(indY%2==0)){ //inverse verticalement
                sourcex=image.width()-1-x%image.width();
                sourcey=y%image.height();
                newimage.pixel(x, y) = image.pixel(sourcex, sourcey);
        }
            else if ((indX%2==1)&&(indY%2==1)){ //inverse tout
                sourcex=image.width()-1-x%image.width();
                sourcey=image.height()-1-y%image.height();
                newimage.pixel(x, y) = image.pixel(sourcex, sourcey);
        }
    }
    }
return newimage;
}

//vérifier dépasse pas, puis que largeur rectangle était bien
void Glitch(sil::Image& image){
int x1{}; //pixel
int y1{};
int x2{};
int y2{};
int h{}; //hauteur rectangle
int l{};//largeur
int nbrect=random_int(1, 80); //nb rectangle
 for (int i{0};i<nbrect;i++){
    x1=random_int(0, image.width()-1);
     y1=random_int(0, image.height()-1);
     x2=random_int(0, image.width()-1);
     y2=random_int(0, image.height()-1);
     h=random_int(1, std::min(10, std::min(image.height() - y1,image.height() - y2))); //hauteur des rect du changement
     l=random_int(1, std::min(20, std::min(image.width() - x1,image.width() - x2))); //largeur sasndépasser image
    //on parcourt les deux rectangle pr échanger
    for (int x{0}; x <l; x++)
    {
        for (int y{0}; y < h; y++)
        {
            std::swap(image.pixel(x1+x,y1+y).r,image.pixel(x2+x,y2+y).r);
            std::swap(image.pixel(x1+x,y1+y).b,image.pixel(x2+x,y2+y).b);
            std::swap(image.pixel(x1+x,y1+y).g,image.pixel(x2+x,y2+y).g);
            
            
            
        }
    }
    

    }
}

void Tri_pixel(sil::Image& image){
    sil::Image origine_image = image;
    int w = origine_image.width();
    int h = origine_image.height();
//on parcourt ligne par ligne
    for(int y=0; y<h; y++){
        int nb = random_int(1, 10); // nbr de rectangles par lignes
        for(int r=0; r<nb; r++){
            //on determine début du glitch et sa longueur
            int x_begin = random_int(0, w-1);
            int longueur = random_int(1, std::min(20, w - x_begin));
            //index car tableau portion est en 1D
            int index_debut = x_begin + y * w;  //on tranforme en 1D
            int index_fin = std::min(index_debut + longueur, (int)origine_image.pixels().size()); //pour ne pas dépasser

            // Copier la portion dans un nv tableau "portion"
            std::vector<glm::vec3> portion(
                origine_image.pixels().begin() + index_debut,
                origine_image.pixels().begin() + index_fin
            );

            // Trier selon luminosité
            std::sort(portion.begin(), portion.end(), [](glm::vec3 const& c1, glm::vec3 const& c2){
                float moy1 = (c1.r + c1.g + c1.b) / 3.f; 
                float moy2 = (c2.r + c2.g + c2.b) / 3.f;
                return moy1 < moy2;
            });

            // Réécrire dans l'image
            for(int i=0; i<(int)portion.size(); i++){
                origine_image.pixels()[index_debut + i] = portion[i];
            }
        }
    }

    // Remplacer l'image originale
    image = origine_image;
}

    



//pour être dans -2 2 on veut une fonction qui quand x=0 donne -2 et quand x=image.width donne 2
sil::Image Fractale(){
    sil::Image image{500, 500};
    float a{};
    float b{}; // z=a+ib
    int itemax=50;
    std::complex<float> c{a, b}; // c=a+ib
    //valeur aléatoire
   for (int x = 0; x < image.width(); x++){
            for (int y = 0; y < image.height(); y++)
            {      
                a= ((x/500.f) *3-2);
                b= ((y/500.f) *3-1.5);
                std::complex<float> c{a, b}; // c=a+ib
                int ite=1;
                std::complex<float> z{0.f, 0.f};
                while (std::abs(z) < 2 && ite< itemax){
                   
                    z=z*z+c;
                    ite+=1;
                    
                
                }
                    float color = ite / itemax;
                    image.pixel(x, y).r = color;
                    image.pixel(x, y).g = color;
                    image.pixel(x, y).b = color;
            }
                   
   }

return image;
               
}

sil::Image DegradeColor1(){

    sil::Image image{300, 200}; //on cree une image en noire 
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            float pourcentage= float(x)/float(image.width() - 1);
             //on cree les vecteurs couleur rouge et vert
             glm::vec3 rouge (1.f,0.f,0.f);
             glm::vec3 vert(0.f,1.f,0.f);
             //couleur mélangée
             glm::vec3 couleur= glm::mix(rouge, vert, pourcentage);
             //couleur au pixel
             image.pixel(x,y).r= couleur.r;
             image.pixel(x,y).b= couleur.b;
             image.pixel(x,y).g= couleur.g;      
        }
    }
    return image;
}
/////////////////////////////////////////////////////////////////////////////////////////
struct Lab{ float L; float a; float b;};
    Lab linear_srgb_to_oklab(glm::vec3 c){
            //transfo oklab
            float l = 0.4122214708f * c.r + 0.5363325363f * c.g + 0.0514459929f * c.b;
	        float m = 0.2119034982f * c.r + 0.6806995451f * c.g + 0.1073969566f * c.b;
	        float s = 0.0883024619f * c.r + 0.2817188376f * c.g + 0.6299787005f * c.b;
            //racine cubique
                float l_ = cbrtf(l);
                float m_ = cbrtf(m);
                float s_ = cbrtf(s);
            // Tranfo en OKLab
            return 
        {0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_,
        1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_,
        0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_,};
}


//on revient en RGB
glm::vec3 oklab_to_linear_srgb(Lab c){
    float l_ = c.L + 0.3963377774f * c.a + 0.2158037573f * c.b;
    float m_ = c.L - 0.1055613458f * c.a - 0.0638541728f * c.b;
    float s_ = c.L - 0.0894841775f * c.a - 1.2914855480f * c.b;
    //puissance 3
    float l = pow(l_,3);
    float m =pow(m_,3);
    float s = pow(s_,3);
    //Tranfo en rgb
       return {
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

glm::vec3 sRGB_to_Linear(glm::vec3 c){
    //on parcourt les 3 composante de c
    for (int i=0;i<3;i++){
        if (c[i]<=0.04045){
            c[i]=c[i]/12.92;
        }
        else{
            c[i]=pow(((c[i]+0.055)/1.055),2.4);
        }
    }
    return c;
}

glm::vec3 Linear_to_sRGB(glm::vec3 l){
    //on parcourt les 3 composante de c
    for (int i=0;i<3;i++){
        if (l[i]<=0.0031308){
            l[i]=l[i]*12.92;
        }
        else{
            l[i]=(pow(l[i],(1/2.4)))*1.055-0.055;
        }
    }
    return l;
}






//application à tous les pixels
sil::Image DegradeColor2(){
    sil::Image image{300,200};
    //on cree les vecteurs couleur rouge et vert
                glm::vec3 rouge (1.f,0.f,0.f);
                glm::vec3 vert(0.f,1.f,0.f);

            //on transforme en lineare puis OKlab
                Lab rougeLab =linear_srgb_to_oklab(sRGB_to_Linear(rouge));
                Lab vertLab = linear_srgb_to_oklab(sRGB_to_Linear(vert));

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++){
                //on fait le mix à lq main
                float pourcentage= float(x)/float(image.width() - 1);
                Lab mixLab;
                mixLab.L = rougeLab.L + pourcentage * (vertLab.L - rougeLab.L);
                mixLab.a = rougeLab.a + pourcentage * (vertLab.a - rougeLab.a);
                mixLab.b = rougeLab.b + pourcentage * (vertLab.b - rougeLab.b);

                
               //interpolation linéaire en OK lab
               glm::vec3 resultat= Linear_to_sRGB(oklab_to_linear_srgb(mixLab));
                //uitlisation de clamp pr rester dans le bon intervalle
                image.pixel(x,y).r= glm::clamp(resultat.r, 0.f,1.f);
                image.pixel(x,y).g= glm::clamp(resultat.g, 0.f,1.f);
                image.pixel(x,y).b= glm::clamp(resultat.b, 0.f,1.f);

        }
    }
        return image;
        }

 ////////////////////////////////////////////////////////////////////////////////////////////////
        //FCT CALCUL LUMINISCNACE
        float Luminisance (glm::vec3& pixel){
            return 0.2126f * pixel.r + 0.7152f * pixel.g + 0.0722f * pixel.b;}

sil::Image Normalisation(sil::Image image) {
    float maxlu = -1.f;
    float minlu = 2.f;

    // recherche min et max
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            float lum = Luminisance(image.pixel(x,y));
            if (lum > maxlu){
             maxlu = lum;}
            if (lum < minlu){
                minlu = lum;}
    }
    }
//vérifie pas division par 0
    float range = maxlu - minlu;
    if (range < 1e-6f) range = 1.f;

    // normalisation
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            glm::vec3 pix = image.pixel(x,y);
            float lum = Luminisance(pix);
            float factor = (lum - minlu) / range;

            image.pixel(x,y).r= pix.r*factor;
            image.pixel(x,y).g= pix.g*factor;
            image.pixel(x,y).b= pix.b*factor;
        }
    }


    return image;}

/////////////////////////////////////////////////////////////////////////////////
//fonction rotation

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

sil::Image Vortex(sil::Image image) {
    sil::Image newimage{image.width(), image.height()}; //nv image 
    //coordonnée du centre
    int Xcentre=image.width()/2;
    int Ycentre=image.height()/2;
    glm::vec2 center {Xcentre,Ycentre};
    float angle=0.f;
    for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                glm::vec2 pos{x, y}; //position actuelle
                float dis=glm::distance(center,pos); //calcule distance
                angle=dis/sqrt(image.width()*image.width()+image.height()*image.height())*40; //distance sur diago * pi2 jsp pq
                glm::vec2 newpos=rotated(pos,center ,angle);//calcule nv position
                int nx = static_cast<int>(newpos.x); //on transfo en entier les coo =rdonnée de la nv position
                int ny = static_cast<int>(newpos.y);
//on vérifie qu'on est pas en dehors de l'image
            if (nx >= 0 && nx < image.width() &&
                ny >= 0 && ny < image.height()) {
                newimage.pixel(x, y) = image.pixel(nx, ny);
            }
            //sinon on fait rien

            }
    }
    return newimage;
}//lisetes de Kernel pour exercices convolution,netteté, contours etc
   float kernel_flou[3][3] = {
        {0.0625,0.125,0.0625},
        {0.125,0.25,0.125},
        {0.0625,0.125,0.0625}
    };

    float kernel_outline[3][3] = {
        {-1,-1,-1},
        {-1,8,-1},
        {-1,-1,-1}
    };
    float kernel_emboss[3][3] = {
        {-2,-1,0},
        {-1,1,1},
        {0,1,2}
    };

    float kernel_sharpen[3][3] = {
        {0,-1,0},
        {-1,5,-1},
        {0,-1,0}
    };
sil::Image Convo(sil::Image& image, float kernel[3][3]){
    sil::Image newimage=image;
 
    //on parcourt notre image 
     for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            //pr stocker le nv couleur
            glm::vec3 nvcolor{0.0f};

            //on parcourt les voisins du px
            for(int dx=-1;dx<=1;dx++){
                for(int dy=-1; dy<=1;dy++){
                    //on verifie que les indices ne sont par hors de l'image
                    int idx= std::min(std::max(x+dx,0), image.width()-1);
                    int idy= std::min(std::max(y+dy,0), image.height()-1);
                    //on applique le kernel
                    nvcolor+=image.pixel(idx,idy)*kernel[dy+1][dx+1];
                    
                }
            }
               newimage.pixel(x,y)=glm::clamp(nvcolor, 0.0f,1.0f);
            }
        
        }
        return newimage;
}






sil::Image Filtre_Separable(sil::Image& image){
//on definit le kernel

    sil::Image resultimage=image;
    sil::Image tempimage=image;
 

    //on sépare le kernel en 2 matrices en faisant 2 listes
    float kernelX[16];
    float kernelY[16];
    for (int j = 0; j < 16; ++j){
        kernelX[j]=1.0f/16;
        kernelY[j]=1.0f/16;}

//passage horizontale

 for (int x{0}; x < image.width(); ++x){
        for (int y{0}; y < image.height(); ++y){
            //on stocke une couleur provisoire
            glm::vec3 tempcolor{0.0f};
            for(int k=0;k<16;k++){
                int idx= std::min(std::max(x+k-16/2,0), image.width()-1);
                tempcolor+=image.pixel(idx,y)*kernelX[k];

            }
            tempimage.pixel(x,y)=tempcolor;
        }
    }
    //passahe varticale
    for (int y = 0; y < image.height(); ++y) {
        for (int x{0}; x < image.width(); ++x){
            glm::vec3 tempcolor{0.0f};
            for(int k=0;k<16;k++){
                int idy= std::min(std::max(y+k-16/2,0), image.height()-1);
                tempcolor+=tempimage.pixel(x,idy)*kernelY[k];
             }
             resultimage.pixel(x,y)=glm::clamp(tempcolor, 0.0f, 1.0f); 
            }
    }
return resultimage;
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

    
     { sil::Image image=Rosace();
        Rosace().save("output/Rosace.png");
    }

     {
       Mosaique(sil::Image{"images/logo.png"}).save("output/Mosaique.png");

    }

    {
       MosaiqueMiroir(sil::Image{"images/logo.png"}).save("output/MosaiqueMiroir.png");

    }
       {
        sil::Image image{"images/logo.png"};
        Glitch(image);
        image.save("output/Glitch.png");
    }

    { sil::Image image=Fractale();
        image.save("output/Fractale.png");
    }

    {sil::Image image = DegradeColor1();
        image.save("output/DegradeColor1.png");
    }

    {sil::Image image = DegradeColor2();
        image.save("output/DegradeColor2.png");
    }

    {
        sil::Image image{"images/photo_faible_contraste.jpg"};
        Normalisation(image).save("output/Normalisation.png");
    }

    {
        sil::Image image{"images/logo.png"};
        Vortex(image).save("output/Vortex.png");
    }

    {sil::Image image{"images/logo.png"};
        Tri_pixel(image);
        image.save("output/Tri.png");}

        {sil::Image image{"images/logo.png"};
        Convo(image,kernel_flou).save("output/Convo.png");}

        {sil::Image image{"images/logo.png"};
        Convo(image,kernel_emboss).save("output/Emboss.png");}

        
        {sil::Image image{"images/logo.png"};
        Convo(image,kernel_outline).save("output/Outline.png");}

        {sil::Image image{"images/logo.png"};
        Convo(image,kernel_sharpen).save("output/Sharpen.png");}

        {sil::Image image{"images/logo.png"};
        Filtre_Separable(image).save("output/Filtre_Separable.png");}
}
