
#include <iostream>

#include "Image.h"
#include "Span.h"
#include "ImageInterpolate.h"

#include "Node.h"
#include "Tree.h"

int main()
{
//    /*
    // Image tirée de l'article de base : "A quasi linear algorithm to compute the tree of shapes.."
    Image<unsigned char> i(5,6);

    std::cout << "image de taille " << i.getH() << "*" << i.getW() << std::endl;


    // 1 ère ligne -> 1 - 1 - 1 - 1 - 1 - 1
    i.setPixel(0,0,1); i.setPixel(0,1,1); i.setPixel(0,2,1); i.setPixel(0,3,1); i.setPixel(0,4,1); i.setPixel(0,5,1);
    // 2 ème ligne -> 1 - 0 - 0 - 3 - 3 - 1
    i.setPixel(1,0,1); i.setPixel(1,1,0); i.setPixel(1,2,0); i.setPixel(1,3,3); i.setPixel(1,4,3); i.setPixel(1,5,1);
    // 3 ème ligne -> 1 - 0 - 1 - 1 - 3 - 1
    i.setPixel(2,0,1); i.setPixel(2,1,0); i.setPixel(2,2,1); i.setPixel(2,3,1); i.setPixel(2,4,3); i.setPixel(2,5,1);
    // 4 ème ligne -> 1 - 0 - 0 - 3 - 3 - 1
    i.setPixel(3,0,1); i.setPixel(3,1,0); i.setPixel(3,2,0); i.setPixel(3,3,3); i.setPixel(3,4,3); i.setPixel(3,5,1);
    // 5 ème ligne -> 1 - 1 - 1 - 1 - 1 - 1
    i.setPixel(4,0,1); i.setPixel(4,1,1); i.setPixel(4,2,1); i.setPixel(4,3,1); i.setPixel(4,4,1); i.setPixel(4,5,1);


    // même image avec des 2 à la place des 1 qui devrait théoriquement conduire au même résultat ...

//    // 1 ère ligne -> 2 - 2 - 2 - 2 - 2 - 2
//    i.setPixel(0,0,5); i.setPixel(0,1,5); i.setPixel(0,2,5); i.setPixel(0,3,5); i.setPixel(0,4,5); i.setPixel(0,5,5);
//    // 2 ème ligne -> 2 - 0 - 0 - 3 - 3 - 2
//    i.setPixel(1,0,5); i.setPixel(1,1,1); i.setPixel(1,2,1); i.setPixel(1,3,9); i.setPixel(1,4,9); i.setPixel(1,5,5);
//    // 3 ème ligne -> 2 - 0 - 2 - 2 - 3 - 2
//    i.setPixel(2,0,5); i.setPixel(2,1,1); i.setPixel(2,2,5); i.setPixel(2,3,5); i.setPixel(2,4,9); i.setPixel(2,5,5);
//    // 4 ème ligne -> 2 - 0 - 0 - 3 - 3 - 2
//    i.setPixel(3,0,5); i.setPixel(3,1,1); i.setPixel(3,2,1); i.setPixel(3,3,9); i.setPixel(3,4,9); i.setPixel(3,5,5);
//    // 5 ème ligne -> 2 - 2 - 2 - 2 - 2 - 2
//    i.setPixel(4,0,5); i.setPixel(4,1,5); i.setPixel(4,2,5); i.setPixel(4,3,5); i.setPixel(4,4,5); i.setPixel(4,5,5);

            //      AUTRE EXEMPLE (ne pas prendre en compte lors de la lecture
    // autre exemple d'image -> la même que celle de base mais en retirant la bordure avec les pixels ayant un niveau de gris à 1

//    Image<unsigned char> i(3,4);
//    i.setPixel(0,0,0); i.setPixel(0,1,0); i.setPixel(0,2,3); i.setPixel(0,3,3);
//    i.setPixel(1,0,0); i.setPixel(1,1,4); i.setPixel(1,2,4); i.setPixel(1,3,3);
//    i.setPixel(2,0,0); i.setPixel(2,1,0); i.setPixel(2,2,3); i.setPixel(2,3,3);


    int h(i.getH()),w(i.getW());

    std::cout << "test " << std::endl;

    std::cout << i << std::endl;
//    */

    /*

    // image tirée de l'article "effective component..."
    // ------------------------
    //
    //      Image utilisée surtout pour voir le résultat des calculs des max et min tree sur un exemple concret


    Image <unsigned char> i (2,5);

    // 1 ère ligne -> 3 - 3 - 1 - 4 - 2
    i.setPixel(0,0,3); i.setPixel(0,1,3); i.setPixel(0,2,1); i.setPixel(0,3,4); i.setPixel(0,4,2);
    // 2 ème ligne -> 4 - 1 - 2 - 3 - 1
    i.setPixel(1,0,4); i.setPixel(1,1,1); i.setPixel(1,2,2); i.setPixel(1,3,3); i.setPixel(1,4,1);

    std::cout << "\033[1;42m\t\tImage de base :\033[0m" << std::endl;

    std::cout << i << std::endl;

    int h(i.getH()),w(i.getW());

//    */

    //                      TESTS CRéTION DES MAX ET MIN-TREE


    int nbP = i.getH() * i.getW();



    //-> Min tree -> connexité 2n


    int* parent_minTree = i.computeMinTree();

    Tree*min_tree = new Tree(parent_minTree,nbP,std::string("MinTree"));

    std::cout << *min_tree << std::endl;

    // -> pour le max-tree -> connexité 3^n -1

    int* parent_maxTree = i.computeMaxTree();

    Tree*max_tree = new Tree(parent_maxTree,nbP,std::string("MaxTree"));

    std::cout << *max_tree << std::endl;



    //                      TEST INTERPOLATIONs

    // test ajout d'une bordure -> fonctionnel

    i.add_edge();

    Image<unsigned char> init (i);

    std::cout << "\033[1;32m Image avec bordure : \033[0m" << std::endl;

    std::cout << i << std::endl;


    // test set-valued map

    std::cout << "Construction de la \033[1;35mset-valued map\033[0m à partir de l'image ayant des bordures" <<std::endl;

    i.set_valued();

    std::cout << i << std::endl;


    // Attention -> pour la version finale on pourra avoir envie de passer l'image de base en paramètre au constructeur de ImageInterpolate
    // dans ce cas, il faudra faire les opérations add_edge() et set_valued() dans le constructeur

    // on passe l'image de base dont on a déjà créé la version set-valued

    ImageInterpolate<unsigned char> u(i);

    displayLegend();

    std::cout << "dimension de U " << u.getH() << "*" << u.getW()<< std::endl;

    // vérifier que l'image obtenue après interpolation correspond bien à ce qui est attendu

    u.displayImage();


    // dans notre cas test équivaut à l'image u (indice b)
    Image<unsigned char> test;

    std::vector<int> r;


    // utilisation de la procédure Sort en passant en paramètre une image vide (dont on modifiera les dimensions pour qu'elle est les
    // même dimension que l'image interpolée ainsi qu'un tableau R qui contiendra les éléments suivant la relation de parenté que l'on
    // souhaite mettre en place

    u.sort(&test,&r,MaxTree);

    // affichage
    std::cout << std::endl;
    std::cout << "affichage de R après utilisation de la fonction sort :" << std::endl;
    std::cout << "\t schématiquement, le parcours de R correspond à un parcours des pixels de l'image en partant des formes les plus externes et en allant"
                 " vers les formes les plus internes" << std::endl << std::endl;


    std::vector<int>::iterator it;
    int compteur(0);
    for (it = r.begin();it != r.end(); it++)
    {
        std::cout << *it << " ";
        compteur ++;
        if (compteur == test.getW())
        {
            compteur =0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "affichage de U(indice b) -> retour de la fonction sort" <<std::endl;

    std::cout << test << std::endl;

    std::cout << "effectue un test sur le tableau R obtenu en sortie de R : on essaye de récupérer uniquement les éléménts de l'image de base" << std::endl;

    int* corresp_test = u.corresponding_2();

    std::vector <int> r_clean ; // version désinterpoler de r qui semble être correct

    compteur = 0;
    int compt_2(0);
    for (it = r.begin();it != r.end(); it++)
    {
        if (corresp_test[*it] != -1)
        {
            std::cout << corresp_test[*it] << " ";
            compteur ++;

            // on ajoute chaque élément que l'on souhaite à r_clean
            r_clean.push_back(corresp_test[*it]);

        }
        if (compteur == w+2)
        {
            compteur =0;
            std::cout << std::endl;
        }
        compt_2++;
    }




    //  application de la fonction union_find sur R qui est un des retours de la fonction sort
    int nbp = test.getH() * test.getW();

    // pour ne pas avoir de problème de type, on doit passer en paramètre à la fonction union_find un tableau d'entier,
    // or R est dans notre cas un vector<int>, on passe alors le pointeur vers le premier élément du vector ce qui donnera un int*
    int * parent = union_find(&r[0],test.getH(),test.getW(),MaxTree);

    // on effectue une autre version de parent avec un union-find que l'on applique à r_clean, il faut encore modifier les dimensions
    // et donner celles de l'image de départ avec les bordures (h+2) et (w+2)

    int *parent_clean = union_find(&r_clean[0],h+2,w+2,MinTree);

    std::cout << "test tableau de correspondance_2 (vérifier que les éléments du tableau parent sont issus de l'image de départ) " << std::endl;

    std::cout << std::endl;



    int compt(0);

    for (compt = 0; compt < u.getH()*u.getW() ; compt++)
        if (corresp_test[compt] != -1)
            std::cout << "n° " << corresp_test[compt] << " : " << compt << std::endl;


    std::cout << "affichage du tableau parent : " << std::endl;

    int j;
    for (j=0; j < nbp; j++)
    {
        if (j%test.getW() == 0)
        {
            std::cout << std::endl;
        }
        std::cout << parent[j] << " ";
    }
    std::cout << std::endl;


    std::cout << "affichage du tableau parent_clean : " << std::endl;

    for (j=0; j < (h+2)*(w+2); j++)
    {
        if (j%(w+2) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << parent_clean[j] << " ";
    }
    std::cout << std::endl;


    // init a été créée plus haut comme étant la copie de l'image de base à laquelle on a ajouté les bordures
    canonize_tree(parent_clean,(h+2)*(w+2),init,&r_clean[0]);

    Tree* treeOfShapes = new Tree (parent_clean,(h+2)*(w+2),"Tree of Shapes");
    std::cout << *treeOfShapes;

//    init.afficheNode(treeOfShapes->getTreeRoot());
//    std::cout << std::endl;
//    init.afficheNode(treeOfShapes->getTreeRoot()->getSons()->at(0));
//    std::cout << std::endl;
//    init.afficheNode(treeOfShapes->getTreeRoot()->getSons()->at(0)->getSons()->at(0));

    init.afficheTree(treeOfShapes);

                                         // canonicalize_tree
    std::cout << "parent_clean (canonicalize version): "<<std::endl;

    for (j=0; j < (h+2)*(w+2); j++)
    {
        if (j%(w+2) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << parent_clean[j] << " ";
    }
    std::cout << std::endl;



    canonize_tree(parent,nbp,test,&r[0]);


    std::cout << "affichage du tableau parent (canonicalize version): " << std::endl;

    for (j=0; j < nbp; j++)
    {
        if (j%test.getW() == 0)
        {
            std::cout << std::endl;
        }
        std::cout << parent[j] << " ";
    }
    std::cout << std::endl;


//    /*
    // un_interpolate(R,parent)
    // -> revient à récupérer l'application inverse de l'interpolation sur R et celle sur parent

    // pour la fonction un_interpolate, on crée un tableau qui prendra en argument un entier correspondant à l'offset
    // d'un élément dans le tableau de notre choix (R ou parent) et qui renverra l'offset correspondant sur l'image
    // s'il existe  ou -1 sinon

    int* corresp = u.corresponding_2 ();


    // pour r_un_interpolate -> prendre la version du dessus avec uniquement les bons éléments gardés lors du parcours de R
//    int* R_un_interpolate  = u.un_interpolate(&r[0], corresp);

    int* parent_un_interpolate = u.un_interpolate(parent,corresp);

    // affichage des 2 tableaux en fonctions des dimensions de l'image de base -> contenues ici dans h et w

    int x,y;

    // problème pour la fonction un_interpolate
    // WARNING -> modification de la dimension pour l'affichage,on prend les valeurs de l'image de base avec ajout de bordure pour les dimensions
    h +=2;
    w +=2;

//    std::cout << std::endl << "R final " << std::endl;

//    for(x = 0; x < h; x++)
//    {
//        for (y = 0; y < w; y++)
//        {
//            std::cout << R_un_interpolate[x*w + y] << " ";
//        }
//        std::cout << std::endl;
//    }

    std::cout << std::endl << "parent final"<< std::endl;

    for(x = 0; x < h; x++)
    {
        for (y = 0; y < w; y++)
        {
            std::cout << parent_un_interpolate[x*w + y] << " ";
        }
        std::cout << std::endl;
    }

    for (x= 0; x < 10; x++)
    {
        std::cout << std::endl;
    }

    // valeur -> correspond à l'offset du premier pixel de la composante
//    std::cout << static_cast<int>(test[288]) << std::endl;

//    std::cout << static_cast<int>(test[612]) << std::endl;


    /* //Vérification U + standardize + corresponding_table -> ok

    std::cout << "vérification de U " << std::endl;

    u.displayImage();
    std::vector<Span <unsigned char> > *test_span = u.standardize();

    typename std::vector<Span<unsigned char> >::iterator ite ;

    int compteur_ =0;

    for (ite = test_span->begin(); ite != test_span->end() ;ite++)
    {
        if (corresp[compteur_ ] != -1)
            std::cout << "\033[7m";
        std::cout << *ite << " ";
        if (corresp[compteur_ ] != -1)
            std::cout << "\033[0m";
        compteur_ ++;
        if (compteur_ % u.getW() == 0)
        {
            std::cout << std::endl;
        }
    }

    compteur_ = 0;


    for (x = 0; x < u.getH()*u.getW(); x++)
    {
        if (corresp[x] != -1)
        {
            compteur_ ++;
            std::cout << test_span->at(x) << " ";
            if (compteur_%w == 0)
            std::cout <<std::endl;
        }
    }

    std::cout << std::endl;
    */

//    std::cout << static_cast<int>(test[232]) << std::endl;

    return 0;
//    */
}

