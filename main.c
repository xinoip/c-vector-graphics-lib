#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pio_vectors.h"

double mysqrt(double x) {
	return sqrt(x);
}

double mysqrt_neg(double x) {
	return -sqrt(x);
}

double justx(double x) {
	return x;
}

double oneoverx(double x) {
	return 100/x;
}

double func1(double x) {
	return (x * (x*x - 6*x + 8)/ ((x-1) * (x-3) * (x-3)));
}

double customwave(double x) {
	return 12*sin(x/12)+100;
}

double customwave2(double x) {
	return sin(x/5)-85;
}

void draw_me(Figure * fig) {

	int i=0;Point2D leg_left[2];Point2D leg_right[2];Point2D arm_left[2];Point2D arm_right[2];Point2D body[2];Point2D nose[3];Point2D floor[2];Point2D rglass[5];Point2D lglass[5];Point2D glassHold[2];Point2D lhold[2];Point2D rhold[2];i=0;leg_left[i++]=get_p_full(-15,-50);leg_left[i++]=get_p_full(0,0);i=0;leg_right[i++]=get_p_full(15,-50);leg_right[i++]=get_p_full(0,0);i=0;body[i++]=get_p_full(0,0);body[i++]=get_p_full(0,65);i=0;arm_right[i++]=get_p_full(0,45);arm_right[i++]=get_p_full(10,13);i=0;arm_left[i++]=get_p_full(0,45);arm_left[i++]=get_p_full(-10,13);i=0;floor[i++]=get_p_full(-250,-50);floor[i++]=get_p_full(250,-50);draw_polyline(fig,floor,2);draw_polyline(fig,leg_left,2);draw_polyline(fig,leg_right,2);draw_polyline(fig,arm_left,2);draw_polyline(fig,arm_right,2);draw_polyline(fig,body,2);draw_circle(fig,get_p(0,80),15);draw_circle(fig,get_p(-7,83),3);draw_circle(fig,get_p(7,83),3);i=0;nose[i++]=get_p_full(0,80);nose[i++]=get_p_full(-3,75);nose[i++]=get_p_full(0,75);draw_polyline(fig,nose,3);draw_circle(fig,get_p(0,70),1);i=0;rglass[i++]=get_p_full(11,87);rglass[i++]=get_p_full(11,79);rglass[i++]=get_p_full(3,79);rglass[i++]=get_p_full(3,87);rglass[i++]=get_p_full(11,87);draw_polyline(fig,rglass,5);i=0;lglass[i++]=get_p_full(-3,87);lglass[i++]=get_p_full(-3,79);lglass[i++]=get_p_full(-11,79);lglass[i++]=get_p_full(-11,87);lglass[i++]=get_p_full(-3,87);draw_polyline(fig,lglass,5);i=0;glassHold[i++]=get_p_full(-4,83);glassHold[i++]=get_p_full(3,83);draw_polyline(fig,glassHold,2);i=0;lhold[i++]=get_p_full(-10,83);lhold[i++]=get_p_full(-13,85);draw_polyline(fig,lhold,2);i=0;rhold[i++]=get_p_full(10,83);rhold[i++]=get_p_full(13,85);draw_polyline(fig,rhold,2);set_color(fig,get_color(255,255,0));draw_circle(fig,get_p(0,200),40);set_color(fig,get_color(255,0,0));draw_fractal_tree(fig,-200,-50,35,10);draw_fractal_tree(fig,200,-50,35,10);set_color(fig,get_color(0,255,0));draw_fractal_atree(fig,-180,-50,25,10);draw_fractal_atree(fig,180,-50,25,10);set_color(fig,get_color(0,0,255));draw_fractal_tree(fig,-220,-50,30,10);draw_fractal_tree(fig,220,-50,30,10);set_color(fig,get_color(0,255,255));draw_fractal_tree(fig,-160,-50,15,10);draw_fractal_tree(fig,160,-50,15,10);
	
}

void draw_space() {
	
	Figure *fig = start_figure(500, 250);

	set_color(fig, get_color(36, 40, 45));
	for(int i = -250; i <= 250; i++) {
		draw_line(fig, get_p_full(i, 125), get_p_full(i, -125));
		
	}

	for(int i = 250, b = 100; i > 0; i--, b-=2) {
		set_color(fig, get_color(36, 40, b));
		draw_circle(fig, get_p(0,5), i);	
	}	

	for(int i = 100, b = 108; i > 0; i--, b--) {
		set_color(fig, get_color(71, 71, b));
		draw_ellipse(fig, i, 35);	
	}

	for(int i = 50, b = 100; i > 0; i--, b-=2) {
		set_color(fig, get_color(36, 40, b));
		draw_circle(fig, get_p(0,5), i);	
	}

	set_color(fig, get_color(36, 40, 135));
	for(int i = -250; i <= 250; i++) {

		for(int y = -125; y <= 125; y++) {

			int x = rand() % 10000;

			if(x == 1) {
				draw_line(fig, get_p_full(i, y), get_p_full(i, y+2));
				draw_line(fig, get_p_full(i, y), get_p_full(i, y-2));
				draw_line(fig, get_p_full(i, y), get_p_full(i+2, y));
				draw_line(fig, get_p_full(i, y), get_p_full(i-2, y));
			} else if(x == 2) {
				draw_fractal_tree(fig, i, y, 5, 2);
			} else if(x == 3) {
				draw_fractal_atree(fig, i, y, 5, 2);
			}

		}

	}

	for(int i = 25, b = 100; i > 0; i--, b-=2) {
		set_color(fig, get_color(36, b, 40));
		draw_circle(fig, get_p(100,-100), i);	
	}

	for(int i = 25, b = 100; i > 0; i--, b-=2) {
		set_color(fig, get_color(b, 40, 40));
		draw_circle(fig, get_p(-167,-37), i);	
	}

	for(int i = 30, b = 100; i > 0; i--, b+=2) {
		set_color(fig, get_color(b, 40, 40));
		draw_circle(fig, get_p(-100,-100), i);	
	}

	for(int i = 30, b = 100; i > 0; i--, b+=2) {
		set_color(fig, get_color(b, b, 40));
		draw_circle(fig, get_p(225,-57), i);	
	}

	for(int i = 30, b = 100; i > 0; i--, b+=2) {
		set_color(fig, get_color(b, 40, b));
		draw_circle(fig, get_p(137,100), i);	
	}

	for(int i = 30, b = 100; i > 0; i--, b+=2) {
		set_color(fig, get_color(b, b, b));
		draw_circle(fig, get_p(-170,50), i);	
	}

	set_color(fig, get_color(41, 63, 97));
	for(int i = 25; i > 0; i--) {
		draw_fx(fig, customwave, -250, 250);
	}

	draw_fractal_tree(fig, 0, -125, 50, 6);
	draw_fractal_tree(fig, 0, -250, 50, 6);
	draw_fractal_tree(fig, 0, 250, 50, 6);

	export_svg(fig, "./space.svg");

	delete_figure(fig);

}

void draw_weather() {

	Figure *fig = start_figure(450, 200);

	set_thickness_resolution(fig, 50, 3);
	
	draw_fx(fig, customwave, -250, 250);
	
	set_thickness_resolution(fig, 0.5, 1);
	for(int i = -250; i <= 250; i++) {

		for(int y = 125; y >= -125; y--) {

			int x = rand() % 100;

			if(x == 1) {
				draw_line(fig, get_p_full(i,y), get_p_full(i,y-1));
			} else if(x == 2) {
				x = rand() % 50;
				if(x == 1) {
					draw_line(fig, get_p_full(i,y), get_p_full(i-2,y-2));
					draw_line(fig, get_p_full(i,y), get_p_full(i+2,y-2));	
				}
			} else if(x == 3) {
				x = rand() % 50;
				if(x == 1) {
					draw_line(fig, get_p_full(i,y), get_p_full(i-2,y+2));
					draw_line(fig, get_p_full(i,y), get_p_full(i+2,y+2));	
				}
				
			}

		}

	}

	set_thickness_resolution(fig, 10, 1);
	draw_line(fig, get_p_full(-225,-98), get_p_full(225,-98));

	draw_line(fig, get_p_full(225,-70), get_p_full(150,-70));
	draw_line(fig, get_p_full(150,-70), get_p_full(125,-98));

	set_thickness_resolution(fig, 20, 1);
	draw_fx(fig, customwave2, -225, 225);

	set_thickness_resolution(fig, 3, 1);
	draw_line(fig, get_p_full(160,-70), get_p_full(165,30));
	draw_line(fig, get_p_full(200,-70), get_p_full(195,30));

	draw_circle(fig, get_p(180, 30), 15);
	set_thickness_resolution(fig, 1.5, 1);
	draw_circle(fig, get_p(180, -30), 5);
	draw_circle(fig, get_p(180, -15), 6);
	draw_circle(fig, get_p(180, 0), 7);
	
	draw_line(fig, get_p_full(-175,-60), get_p_full(-160,-75));	
	draw_line(fig, get_p_full(-110,-75), get_p_full(-160,-75));	
	draw_line(fig, get_p_full(-110,-75), get_p_full(-95,-60));	
	draw_line(fig, get_p_full(-135,-75), get_p_full(-135,-30));	
	draw_line(fig, get_p_full(-135,-30), get_p_full(-145,-30));	
	draw_line(fig, get_p_full(-135,-40), get_p_full(-145,-30));	

	draw_line(fig, get_p_full(-135,-60), get_p_full(-120,-75));	
	draw_line(fig, get_p_full(-70,-75), get_p_full(-120,-75));	
	draw_line(fig, get_p_full(-70,-75), get_p_full(-55,-60));	
	draw_line(fig, get_p_full(-95,-75), get_p_full(-95,-30));	
	draw_line(fig, get_p_full(-95,-30), get_p_full(-105,-30));	
	draw_line(fig, get_p_full(-95,-40), get_p_full(-105,-30));	

	export_eps(fig, "./weather.eps");
	delete_figure(fig);

}

Tree* newNode(int data) { 
    Tree* node = (Tree*) malloc(sizeof(Tree)); 
    node->data = data; 
    node->left = NULL; 
    node->right = NULL;
  
    return(node); 
} 

int main() {
	
	Figure *db_graphs = start_figure(500,500);
	Figure *db_fractals = start_figure(1000,1000);
	Figure *db_bintree = start_figure(1000,1000);
	Figure *db_resize = start_figure(100,100);
	Figure *db_import;
	Figure *me = start_figure(500,500);

	printf("\n\nDrawing something rainy...\n\n");
	draw_weather();

	printf("\n/********************************************************/\n");
	printf("DEMO BLOCK graphs, circles, ellipses");
	printf("\n/********************************************************/\n");

	/********************************************************/
	//DEMO BLOCK graphs, circles, ellipses, resolutions, thickness
	/********************************************************/

	/* X-Y axis */
	set_color(db_graphs, get_color(0,0,0));
	set_thickness_resolution(db_graphs, 0.1, 1);
	draw_cartesian(db_graphs);

	/* Square root of X graph */
	set_color(db_graphs, get_color(255,0,0));
	set_thickness_resolution(db_graphs, 0.1, 1);
	//It deals with NaN points in the interval as well
	//mysqrt function is defined on 0 to positive infinity
	//But programmer can call the function with any interval without knowing the defined interval
	//Function drawfx will deal with it
	draw_fx(db_graphs, mysqrt, -100, 100);

	/* Negative of Square root of X graph */
	set_color(db_graphs, get_color(0,0,255));
	set_thickness_resolution(db_graphs, 0.1, 5);
	draw_fx(db_graphs, mysqrt_neg, 0, 600);

	/* One ove X graph */
	set_color(db_graphs, get_color(0,255,255));
	set_thickness_resolution(db_graphs, 0.1, 3);
	draw_fx(db_graphs, oneoverx, -100, 100);

	/* Custom function graph with lots of y goes to infinity conditions */
	set_color(db_graphs, get_color(255,0,0));
	set_thickness_resolution(db_graphs, 0.1, 10);
	draw_fx(db_graphs, func1, -100, 100);

	/* Circle graph */
	set_color(db_graphs, get_color(255,255,0));
	set_thickness_resolution(db_graphs, 1, 3);
	draw_circle(db_graphs, get_p(-50,-50), 50);

	/* Anothe circle graph */
	//Programmer can use negative resolution values
	//This resolution values will result to data lose and more blocky images
	set_color(db_graphs, get_color(255,255,0));
	set_thickness_resolution(db_graphs, 1, -3);
	draw_circle(db_graphs, get_p(0,0), 50);

	/* Ellipse graph */
	set_color(db_graphs, get_color(255,0,0));
	set_thickness_resolution(db_graphs, 0.1, 100);
	draw_ellipse(db_graphs, 20, 10);

	/* Exporting files */
	export_eps(db_graphs, "./db_graphs.eps");
	export_svg(db_graphs, "./db_graphs.svg");

	/* Scaling the graphs for demo */
	scale_figure(db_graphs, 2, 2);

	/* Exporting files again as scaled */
	export_eps(db_graphs, "./db_graphsScaled.eps");
	export_svg(db_graphs, "./db_graphsScaled.svg");

	delete_figure(db_graphs);

	/********************************************************/
	//END OF DEMO BLOCK graphs, circles, ellipses, resolutions, thickness
	/********************************************************/
	
	printf("\n/********************************************************/\n");
	printf("DEMO BLOCK fractal trees");
	printf("\n/********************************************************/\n");

	/********************************************************/
	//DEMO BLOCK fractal trees, color, thickness
	/********************************************************/

	set_color(db_fractals, get_color(255,0,0));
	set_thickness_resolution(db_fractals, 0.1, 100);
	draw_fractal_tree(db_fractals ,0, -(db_fractals->height)/2, 100, 14);

	set_thickness_resolution(db_fractals, 1, 100);
	set_color(db_fractals, get_color(0,255,0));
	draw_fractal_tree(db_fractals ,0, -(db_fractals->height)/2, 50, 17);

	set_thickness_resolution(db_fractals, 0.5, 100);
	set_color(db_fractals, get_color(0,255,255));
	draw_fractal_atree(db_fractals ,0, -(db_fractals->height)/2, 25, 14);

	/* Exporting files */
	export_eps(db_fractals, "./db_fractals.eps");
	export_svg(db_fractals, "./db_fractals.svg");

	/* Scaling the fractals for demo */
	scale_figure(db_fractals, 5, 5);

	/* Exporting files again as scaled */
	export_eps(db_fractals, "./db_fractalsScaled.eps");
	export_svg(db_fractals, "./db_fractalsScaled.svg");
	
	delete_figure(db_fractals);

	/********************************************************/
	//END OF DEMO BLOCK fractal trees, color, thickness
	/********************************************************/

	printf("\n/********************************************************/\n");
	printf("DEMO BLOCK binary tree");
	printf("\n/********************************************************/\n");

	/********************************************************/
	//DEMO BLOCK binary tree
	/********************************************************/

	/* Creation of tree */
	//Binarytree structure is defined in the library
	Tree *mytree = newNode(10);
	mytree->left = newNode(100);
	mytree->right = newNode(89);
	
	mytree->left->left = newNode(4);
	mytree->left->right = newNode(11);
	
	mytree->right->left = newNode(31);
	mytree->right->right = newNode(54);
	mytree->right->right->right = newNode(54);
	
	mytree->right->left->left = newNode(62);
	mytree->left->right->right = newNode(100);
	
	mytree->right->left->left->left = newNode(666);
	mytree->left->right->right->right = newNode(999);
	
	mytree->right->left->left->left->left	= newNode(665);
	mytree->left->right->right->right->right = newNode(998);
	
	/* Drawing the binary tree */
	set_color(db_bintree, get_color(255, 0, 0));
	draw_binary_tree(db_bintree, mytree, get_p_full(0, 0));

	/* Scaling the figure down because it is a big tree */
	scale_figure(db_bintree, 0.5, 0.5);

	/* Exporting files */
	export_eps(db_bintree, "./db_bintree.eps");

	delete_figure(db_bintree);
	
	/********************************************************/
	//END OF DEMO BLOCK binary tree
	/********************************************************/

	printf("\n/********************************************************/\n");
	printf("DEMO BLOCK polyline and resize");
	printf("\n/********************************************************/\n");

	/********************************************************/
	//DEMO BLOCK polyline and resize
	/********************************************************/

	Point2D pointarr[5];
	pointarr[0] = get_p_full(0, 50);
	pointarr[1] = get_p_full(50, 0);
	pointarr[2] = get_p_full(0, -50);
	pointarr[3] = get_p_full(-50, 0);
	pointarr[4] = get_p_full(0, 50);
	draw_polyline(db_resize, pointarr, 5);

	/* Exporting files */
	export_eps(db_resize, "./db_resizeBefore.eps");

	/* Resize figure for demo */
	resize_figure(db_resize, get_p_full(-30, -30), get_p_full(30, 30));

	/* Exporting files after resize */
	export_eps(db_resize, "./db_resizeAfter.eps");
	
	delete_figure(db_resize);

	/********************************************************/
	//END OF DEMO BLOCK polyline and resize
	/********************************************************/

	printf("\n/********************************************************/\n");
	printf("DEMO BLOCK appendfigures");
	printf("\n/********************************************************/\n");

	/********************************************************/
	//DEMO BLOCK appendfigures
	/********************************************************/

	Figure *myf1 = start_figure(500,500);
	Figure *myf2 = start_figure(500, 500);
	Figure *myf3 = start_figure(500, 500);
	Figure *myf4 = start_figure(500, 500);
	
	/* Draw a circle on myf1 */
	set_color(myf1, get_color(255,0,0));
	set_thickness_resolution(myf1, 3, 100);
	draw_circle(myf1, get_p(60, 60), 50);
	
	/* Draw a fractal tree on myf2 */
	set_color(myf2, get_color(0,255,0));
	set_thickness_resolution(myf2, 0.1, 100);
	draw_fractal_tree(myf2 ,0, -(myf2->height)/2, 100, 14);
	
	/* Draw an ellipse on myf3 */
	set_color(myf3, get_color(0,0,255));
	set_thickness_resolution(myf3, 3, 100);
	draw_ellipse(myf3, 20, 10);
	
	/* Draw an asymetrical fractal tree on myf4 */
	set_color(myf4, get_color(0,0,0));
	set_thickness_resolution(myf4, 0.1, 100);
	draw_fractal_atree(myf4 ,0, -(myf2->height)/2, 50, 14);
	
	/* Append everything into myf1 */
	append_figures(myf1, myf2);
	append_figures(myf1, myf3);
	append_figures(myf1, myf4);
	
	/* Export files */
	export_eps(myf1, "./db_append.eps");
	export_svg(myf1, "./db_append.svg");

	delete_figure(myf4);
	delete_figure(myf3);
	delete_figure(myf2);

	/********************************************************/
	//END OF DEMO BLOCK appendfigures
	/********************************************************/

	printf("\n/********************************************************/\n");
	printf("DEMO BLOCK import svg");
	printf("\n/********************************************************/\n");

	/********************************************************/
	//DEMO BLOCK import svg
	/********************************************************/

	/* Let's import the last created db_append.svg */
	import_svg("./db_append.svg", &db_import);

	/* Add a circle to it */
	Figure *foocircle = start_figure(500,500);
	draw_circle(foocircle, get_p(0,25), 100);
	append_figures(db_import, foocircle);
	
	/* Export the imported new svg */ 	
	export_svg(db_import, "./db_import.svg");

	delete_figure(db_import);

	/********************************************************/
	//END OF DEMO BLOCK import svg
	/********************************************************/

	printf("\n\nDrawing a giant...\n\n");
	draw_me(me);
	export_eps(me, "./itsme.eps");
	delete_figure(me);	

	printf("\n\nDrawing something like a galaxy...\n\n");
	draw_space();

	//draw_weather();

	printf("\n/********************************************************/\n");
	printf("\nEND OF DEMO\n\n");
	printf("Project: Library for creating EPS and SVG vector graphics in C.\n");
	printf("Author: Buğra Eren Yılmaz\n");
	printf("Supervisor: \n");
	printf("\nGebze Technical University\n");
	printf("\n/********************************************************/\n\n");

}
