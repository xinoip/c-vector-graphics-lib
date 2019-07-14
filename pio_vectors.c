#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pio_vectors.h"

#define PI 3.14

void delete_figure(Figure * fig) {

	Path *curr, *prev;
	
	printf("Deleting figure ... ");
	
	for(int i = 0; i < fig->data_len; i++) {
		curr = fig->data[i];

		while(curr != NULL) {
			prev = curr;

			curr = curr->next;

			free(prev->point);
			free(prev);			
		}
		
	}

	printf("deleted %d paths!\n", fig->data_len);

	free(fig->data);
	free(fig);

}

/* Create color and return it */
Color get_color(int r, int g, int b) {
	Color rtr;
	rtr.r = r;
	rtr.g = g;
	rtr.b = b;
	return rtr;
}

/* Create point and return it */
Point2D get_p_full(double x, double y) {
	Point2D rtr = {x, y};
	return rtr;
}

/* Create point pointer and return it */
Point2D * get_p(double x, double y) {
	Point2D *rtr = (Point2D *)malloc(sizeof(Point2D));
	rtr->x = x;
	rtr->y = y;
	return rtr;
}

/* Returns a pointer to path node (path is linkedlist) */
Path * create_path(Point2D * point, int skip, Figure *fig) {
	Path *rtr = (Path *)malloc(sizeof(Path));
	rtr->point = point;
	rtr->skip = skip;
	rtr->next = NULL;
	rtr->fcolor = get_color(fig->fcolor.r, fig->fcolor.g, fig->fcolor.b);
	rtr->thickness = fig->thickness;
	return rtr;
}

/* Start width*height figure */
Figure * start_figure(double width, double height) {
	
	Figure *rtr = (Figure *)malloc(sizeof(Figure));
	
	rtr->width = width;
	rtr->height = height;
	rtr->thickness = 1;
	rtr->resolution = 1;
	//rtr->fcolor = {0, 0, 0};
	
	rtr->data_cap = 100;
	rtr->data = malloc(sizeof(Path *) * rtr->data_cap);
	
	rtr->data_len = 0;
	rtr->font_len = 0;
	
	return rtr;
	
}

void set_color(Figure * fig, Color c) {
	fig->fcolor.r = c.r;
	fig->fcolor.g = c.g;
	fig->fcolor.b = c.b;
}

void set_thickness_resolution(Figure * fig, double thickness, double resolution) {
	fig->thickness = thickness;
	fig->resolution = resolution;
}

void draw_cartesian(Figure * fig) {
	int root_i = fig->data_len;
	fig->data[root_i] = create_path(get_p(-(fig->width) / 2,0), 0, fig);
	fig->data_len += 1;
	fig->data[root_i]->next = create_path(get_p((fig->width) / 2,0), 0, fig);
	
	root_i++;
	fig->data[root_i] = create_path(get_p(0,-(fig->height) / 2), 0, fig);
	fig->data_len += 1;
	fig->data[root_i]->next = create_path(get_p(0, (fig->height) / 2), 0, fig);
	
}

void draw_fx(Figure * fig, double f(double x), double start_x, double end_x) {
	
	double diffx;
	if(fig->resolution > 11) {
		diffx = pow(2, -10);
		
	} else if(fig->resolution < 0){
		printf("Resolution warning! Resolution value is negative, correct imaging not guaranteed!\n");
		diffx = pow(2, -(fig->resolution));
		
	} else {
		diffx = pow(2, -(fig->resolution - 1));
		
	}
	
	double curr_x = start_x, curr_y = f(curr_x);
	
	int root_i = fig->data_len;
	if(root_i >= fig->data_cap) {
		fig->data_cap += 100;
		fig->data = realloc(fig->data, sizeof(Path *) * fig->data_cap);
	}
	fig->data[root_i] = create_path(get_p(0,0), 0, fig);
	fig->data_len += 1;
	
	Path *curr_root = fig->data[root_i];
	
	while(isnan(curr_y) || isinf(curr_y)) {
		curr_x += diffx;
		curr_y = f(curr_x);
	}
	
	curr_root->point->x = curr_x;
	curr_root->point->y = curr_y;
	curr_root->skip = 0;
	printf("Drawing started at %lf,%lf, ", curr_x, curr_y);
	
	while(curr_x <= end_x) {
		curr_y = f(curr_x);
		
		if(isnan(curr_y) || isinf(curr_y)) {
			curr_root->next = create_path(get_p(curr_x, curr_y), 1, fig);	
		
		} else {
			curr_root->next = create_path(get_p(curr_x, curr_y), 0, fig);	
			
		}
		
		curr_root = curr_root->next;
		curr_x += diffx;
	}
	
	printf("ended at %lf,%lf\n", curr_x, curr_y);
	
}

double halfcircle_up(Point2D * center, double r, double x) {
	return (sqrt( (r*r) - ( (x - center->x) * (x - center->x) ) ) + center->y);
}

double halfcircle_down(Point2D * center, double r, double x) {
	return (-sqrt( (r*r) - ( (x - center->x) * (x - center->x) ) ) + center->y);
}

void draw_halfcircle(Figure * fig, double f(Point2D * center, double r, double x), Point2D * center, double r) {
	
	double diffx;
	if(fig->resolution > 11) {
		diffx = pow(2, -10);
		
	} else if(fig->resolution < 0){
		printf("Resolution warning! Resolution value is negative, correct imaging not guaranteed!\n");
		diffx = pow(2, -(fig->resolution));
		
	} else {
		diffx = pow(2, -(fig->resolution - 1));
		
	}
	
	double curr_x = center->x - r, end_x = center->x + r;
	double curr_y = f(center, r, curr_x);
	
	int root_i = fig->data_len;
	if(root_i >= fig->data_cap) {
		fig->data_cap += 100;
		fig->data = realloc(fig->data, sizeof(Path *) * fig->data_cap);
	}
	fig->data[root_i] = create_path(get_p(0,0), 0, fig);
	fig->data_len += 1;
	
	Path *curr_root = fig->data[root_i];
	
	curr_root->point->x = curr_x;
	curr_root->point->y = curr_y;
	curr_root->skip = 0;
	
	while(curr_x <= end_x) {
		curr_y = f(center, r, curr_x);
		
		curr_root->next = create_path(get_p(curr_x, curr_y), 0, fig);	
		
		curr_root = curr_root->next;
		curr_x += diffx;
	}
	
}

void draw_circle(Figure * fig, Point2D * center, double r) {
	printf("Drawing circle centered at %lf,%lf, with %lf radius\n", center->x, center->y, r);
	draw_halfcircle(fig, halfcircle_up, center, r);
	draw_halfcircle(fig, halfcircle_down, center, r);
}

double halfellipse_up(double A, double B, double x) {
	return (B/A) * sqrt(-((x*x) - (A*A)));
}

double halfellipse_down(double A, double B, double x) {
	return -(B/A) * sqrt(-((x*x) - (A*A)));
}

void draw_halfellipse(Figure *fig, double f(double, double, double), double A, double B) {
	
	double diffx;
	if(fig->resolution > 11) {
		diffx = pow(2, -10);
		
	} else if(fig->resolution < 0){
		printf("Resolution warning! Resolution value is negative, correct imaging not guaranteed!\n");
		diffx = pow(2, -(fig->resolution));
		
	} else {
		diffx = pow(2, -(fig->resolution - 1));
		
	}
	
	double curr_x = -A, end_x = A;
	double curr_y = f(A, B, curr_x);
	
	int root_i = fig->data_len;
	if(root_i >= fig->data_cap) {
		fig->data_cap += 100;
		fig->data = realloc(fig->data, sizeof(Path *) * fig->data_cap);
	}
	fig->data[root_i] = create_path(get_p(0,0), 0, fig);
	fig->data_len += 1;
	
	Path *curr_root = fig->data[root_i];
	
	curr_root->point->x = curr_x;
	curr_root->point->y = curr_y;
	curr_root->skip = 0;
	
	while(curr_x <= end_x) {
		curr_y = f(A, B, curr_x);
		
		curr_root->next = create_path(get_p(curr_x, curr_y), 0, fig);	
		
		curr_root = curr_root->next;
		curr_x += diffx;
	}
	
}

void draw_ellipse(Figure *fig, double A, double B) {
	printf("Drawing ellipse\n");
	draw_halfellipse(fig, halfellipse_up, A, B);
	draw_halfellipse(fig, halfellipse_down, A, B);
}

int height(Tree* node) { 
    if (node==NULL) 
        return 0; 
    else
    { 
        /* compute the height of each subtree */
        int lheight = height(node->left); 
        int rheight = height(node->right); 
  
        /* use the larger one */
        if (lheight > rheight) 
            return(lheight+1); 
        else return(rheight+1); 
    } 
} 

void draw_line(Figure *fig, Point2D sp, Point2D ep) {

	Point2D arr[2];
	arr[0] = sp;
	arr[1] = ep;

	draw_polyline(fig, arr, 2);

}

void create_line(Figure **fig, Point2D sp, Point2D ep) {
	
	int root_i = (*fig)->data_len;
	(*fig)->data_len += 1;
	if(root_i >= (*fig)->data_cap) {
		(*fig)->data_cap += 100;
		(*fig)->data = realloc((*fig)->data, sizeof(Path *) * (*fig)->data_cap);
	}
	(*fig)->data[root_i] = create_path(get_p(sp.x, sp.y), 0, (*fig));
	(*fig)->data[root_i]->next = create_path(get_p(ep.x, ep.y), 0, (*fig));
	
}

void create_font(Figure **fig, Point2D p, int scale, int data, Color c) {
	
	Font newf;
	newf.point = p;
	newf.scale_val = scale;
	newf.data = data;
	newf.fcolor = c;
	
	int root_i = (*fig)->font_len;
	(*fig)->font_len += 1;
	
	(*fig)->fonts[root_i] = newf;
	
}

void draw_binary_tree_helper(Figure *fig, Tree * root, Point2D center, double diffx) {

	double diffy = 30, r  = 15;

	if(root == NULL) return;

	draw_circle(fig, &center, r);
	create_font(&fig, get_p_full(center.x-15, center.y), 12, root->data, get_color(255, 0, 0));
	
	if(root->left != NULL) {
		create_line(&fig, center, get_p_full(center.x - diffx/2, center.y - diffy));
		draw_binary_tree_helper(fig, root->left, get_p_full(center.x - diffx/2, center.y - diffy), diffx/2);
		
	}
	
	if(root->right != NULL) {
		create_line(&fig, center, get_p_full(center.x + diffx/2, center.y - diffy));
		draw_binary_tree_helper(fig, root->right, get_p_full(center.x + diffx/2, center.y - diffy), diffx/2);
		
		
	}
	
}

void draw_binary_tree(Figure *fig, Tree * root, Point2D center) {

	printf("Drawing binary tree");
	double diffx = height(root) * (100);
	draw_binary_tree_helper(fig, root, center, diffx);
	
}

void scale_figure(Figure * fig, double scale_x, double scale_y) {
	
	Path *curr_path;
	
	printf("Scaling figure\n");

	for(int i = 0; i < fig->data_len; i++) {
		curr_path = fig->data[i];
	
		while(curr_path != NULL) {
			curr_path->point->x *= scale_x;
			curr_path->point->y *= scale_y;	
			curr_path = curr_path->next;
		}
	}
	
	for(int i = 0; i < fig->font_len; i++) {
		fig->fonts[i].point.x *= scale_x;
		fig->fonts[i].point.y *= scale_y;
		fig->fonts[i].scale_val *= scale_y+scale_x/2;	
	}
	
}

void draw_polyline(Figure * fig, Point2D * poly_line, int n) {
	
	int root_i = fig->data_len;
	if(root_i >= fig->data_cap) {
		fig->data_cap += 100;
		fig->data = realloc(fig->data, sizeof(Path *) * fig->data_cap);
	}
	fig->data[root_i] = create_path(get_p(0,0), 0, fig);
	fig->data_len += 1;
	
	Path *curr_root = fig->data[root_i];
	
	curr_root->point->x = poly_line[0].x;
	curr_root->point->y = poly_line[0].y;
	curr_root->skip = 0;
	
	for(int i = 1; i < n; i++) {	
		
		curr_root->next = create_path(get_p(poly_line[i].x, poly_line[i].y), 0, fig);
		curr_root = curr_root->next;
	
	}
	
}

void draw_fractal_atree_helper(Figure * fig, double center_x, double center_y, int size, int num_iterations, double alpha) {
	
	double theta = PI/6;
	
	Point2D rp, center;
	
	if(num_iterations != 0) {		
		center.x = center_x;
		center.y = center_y;
		
		rp.x = center_x + (cos(alpha) * size);
		rp.y = center_y + (sin(alpha) * size);
		create_line(&fig, center, rp);
		
		draw_fractal_atree_helper(fig, rp.x, rp.y, size*0.80, num_iterations-1, alpha-theta);
		draw_fractal_atree_helper(fig, rp.x, rp.y, size*0.80, num_iterations-1, alpha+ theta/2);
	
		
	} else {
		return;
		
	}
	
}

void draw_fractal_tree_helper(Figure * fig, double center_x, double center_y, int size, int num_iterations, double alpha) {
	
	double theta = PI/10;
	
	Point2D rp, center;
	
	if(num_iterations != 0) {		
		center.x = center_x;
		center.y = center_y;
		
		rp.x = center_x + (cos(alpha) * size);
		rp.y = center_y + (sin(alpha) * size);
		create_line(&fig, center, rp);
		
		draw_fractal_tree_helper(fig, rp.x, rp.y, size*0.80, num_iterations-1, alpha-theta);
		draw_fractal_tree_helper(fig, rp.x, rp.y, size*0.80, num_iterations-1, alpha+theta);
	
		
	} else {
		return;
		
	}
	
}

void draw_fractal_tree(Figure *fig, double center_x, double center_y, int size, int num_iterations) {
	
	draw_fractal_tree_helper(fig, center_x, center_y, size, num_iterations, PI/2);
	
}

void draw_fractal_atree(Figure *fig, double center_x, double center_y, int size, int num_iterations) {
	
	draw_fractal_atree_helper(fig, center_x, center_y, size, num_iterations, PI/2);
	
}

void resize_figure(Figure *fig, Point2D start_roi, Point2D end_roi) {
	fig->height = end_roi.y - start_roi.y;
	fig->width = end_roi.x - start_roi.x;	
}

void append_figures(Figure * fig1, Figure * fig2) {
	
	Path *curr_path; 
	int root_i = fig1->data_len;
	
	printf("Appending figures ...");
	
	for(int i = 0; i < fig2->data_len; i++) {
		
		curr_path = fig2->data[i];
		
		if(root_i >= fig1->data_cap) {
			fig1->data_cap += 100;
			fig1->data = realloc(fig1->data, sizeof(Path *) * fig1->data_cap);
		}
		fig1->data[root_i++] = curr_path;
		fig1->data_len += 1;
		
	}
	
	printf("Done!\n");
	
}

/* Returns line no of a file */
int get_line_file(char * file_name) {
	
	FILE *fin = fopen(file_name, "r");
	
	int rtr = 0;
	char c;
	
	while(!feof(fin)) {
		
		fscanf(fin, "%c", &c);
		
		if(c == '\n') rtr++;
		
	}
	
	fclose(fin);
	
	return rtr;
	
}

void import_svg(char * file_name, Figure ** fig) {
	
	int fileLen = get_line_file(file_name);
	
	printf("Importing svg file with %d lines ... ", fileLen);
	
	FILE *fin = fopen(file_name, "r");
	
	double height, width;
	
	if(fin == NULL) {
		return;
	}
	
	fscanf(fin, "<svg height=\"%lf\" width=\"%lf\">\n", &height, &width);
	(*fig) = start_figure(width, height);
		
	double fix_x = (*fig)->width / 2;
	double fix_y = (*fig)->height / 2;
	
	printf("%lf %lf\n", width, height);
	
	
	int i = 0;
	double x1, x2, y1, y2, thic;
	int r, g, b;
	
	while(i < fileLen) {
	
		fscanf(fin, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(%d,%d,%d);stroke-width:%lf\" />\n", &x1, &y1, &x2, &y2, &r, &g, &b, &thic);
		
		if(i >= (*fig)->data_cap) {
			(*fig)->data_cap += 100;
			(*fig)->data = realloc((*fig)->data, sizeof(Path *) * (*fig)->data_cap);
		}
		
		(*fig)->data[i] = (Path *)malloc(sizeof(Path));
		(*fig)->data[i]->point = get_p(x1-fix_x, y1-fix_y);
		(*fig)->data[i]->fcolor = get_color(r, g, b);
		(*fig)->data[i]->thickness = thic;
		(*fig)->data[i]->skip = 0;
		
		(*fig)->data[i]->next = (Path *)malloc(sizeof(Path));
		(*fig)->data[i]->next->point = get_p(x2-fix_x, y2-fix_y);
		(*fig)->data[i]->next->fcolor = get_color(r, g, b);
		(*fig)->data[i]->next->thickness = thic;
		(*fig)->data[i]->next->skip = 0;
		(*fig)->data[i]->next->next = NULL;
		
		(*fig)->data_len++;
		
		i++;
		
	}
	
	printf("Done!\n");
	
}

void export_eps(Figure * fig, char * file_name) {
	
	FILE *fout = fopen(file_name, "w");
	Path *curr_path;
	
	int need_move = 1;
	
	double llx = -(fig->width / 2);
	double lly = -(fig->height / 2);
	double urx = fig->width / 2;
	double ury = fig->height / 2;
	
	if(fout != NULL) {
		fprintf(fout, "%%!PS-Adobe-3.0 EPSF-3.0\n");
		fprintf(fout, "%%%%BoundingBox: %lf %lf %lf %lf\n", llx, lly, urx, ury);

		/* Draw Paths */
		for(int i = 0; i < fig->data_len; i++) {
			curr_path = fig->data[i];
			need_move = 1;
			fprintf(fout, "%d %d %d setrgbcolor\n", curr_path->fcolor.r, curr_path->fcolor.g, curr_path->fcolor.b);
			fprintf(fout, "%lf setlinewidth\n", curr_path->thickness);
			
			while(curr_path != NULL) {
				if(curr_path->skip == 1) {
					need_move = 1;
					
				} else {
					if(need_move == 1) {
						fprintf(fout, "%lf %lf moveto\n", curr_path->point->x, curr_path->point->y);
						need_move = 0;
					}
					
					if(curr_path->next != NULL) {
						if(curr_path->next->skip == 1) {
							need_move = 1;
							
						} else {
							if(curr_path->next == NULL) {
								fprintf(fout, "%lf %lf lineto\n", curr_path->point->x, curr_path->point->y);
							} else {
								fprintf(fout, "%lf %lf lineto %lf %lf lineto\n", 
								curr_path->point->x, curr_path->point->y, curr_path->next->point->x, curr_path->next->point->y);
							}	
							
						}
					} else {
						fprintf(fout, "%lf %lf lineto\n", curr_path->point->x, curr_path->point->y);
						
					}
					
				}

				curr_path = curr_path->next;
			}
			
			fprintf(fout, "stroke\n");
		}
		
		/* Draw Fonts */
		for(int i = 0; i < fig->font_len; i++) {
			fprintf(fout, "%d %d %d setrgbcolor\n", fig->fonts[i].fcolor.r, fig->fonts[i].fcolor.g, fig->fonts[i].fcolor.b);
			fprintf(fout, "/Helvetica findfont\n");
			fprintf(fout, "%d scalefont setfont\n", fig->fonts[i].scale_val);
			fprintf(fout, "%lf %lf moveto\n", fig->fonts[i].point.x, fig->fonts[i].point.y);
			fprintf(fout, "(%d) show\n", fig->fonts[i].data);
		}
		
		printf("Vector file exported as eps to \"%s\"\n", file_name);
		
	} else {
		printf("#1 Error in export_eps!");
		exit(1);
		
	}
	
}

void export_svg(Figure * fig, char * file_name) {

	FILE *fout = fopen(file_name, "w");
	Path *curr_path;
	
	int need_move = 1;
	
	double llx = -(fig->width / 2);
	double lly = -(fig->height / 2);
	double urx = fig->width / 2;
	double ury = fig->height / 2;
	
	double fix_x = fig->width / 2;
	double fix_y = (fig->height / 2);
	
	if(fout != NULL) {
		fprintf(fout, "<svg height=\"%lf\" width=\"%lf\">\n", fig->height, fig->width);
		
		/* Draw Paths */
		for(int i = 0; i < fig->data_len; i++) {
			curr_path = fig->data[i];
			
			while(curr_path != NULL) {
				if(curr_path->skip == 1) {
					need_move = 1;
					
				} else {
					if(need_move == 1) {
						curr_path = curr_path->next;
						need_move = 0;
					}
					
					if(curr_path->next != NULL) {
						if(curr_path->next->skip == 1) {
							need_move = 1;
							
						} else {						
							fprintf(fout, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(%d,%d,%d);stroke-width:%lf\" />\n",
							curr_path->point->x+fix_x, curr_path->point->y+fix_y, curr_path->next->point->x+fix_x, curr_path->next->point->y+fix_y, curr_path->fcolor.r, curr_path->fcolor.g, curr_path->fcolor.b, fig->thickness);
						}
					} else {
						
						
					}
					
				}
				
				//fprintf(fout, "\n");
				curr_path = curr_path->next;
			}
			
		}
		
		fprintf(fout, "</svg>\n");
		
		printf("Vector file exported as svg to \"%s\"\n", file_name);
		
	} else {
		printf("#1 Error in export_eps!");
		exit(1);
		
	}
	
}