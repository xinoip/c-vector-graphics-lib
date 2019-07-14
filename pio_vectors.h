/* Basic 2D point */
typedef struct Point2D_s {
	double x, y;
} Point2D;

/* Tree implementation for binary tree drawing */
typedef struct Tree_s {
	int data;
	int position;
	struct Tree_s *left, *right;
} Tree;

/* RGB Color */
typedef struct Color_s {
	int r, g, b;
} Color;

/* Path as a linkedlist (connected points) */
typedef struct Path_s {
	Point2D *point;
	int skip;
	Color fcolor;
	double thickness;
	struct Path_s *next;
} Path;

/* Font with color, position, and size */
typedef struct Font_s {
	Point2D point;
	Color fcolor;
	int data;
	int scale_val;
} Font;

/* Figure */
/* Every figure holds it's path's roots in an array */
typedef struct Figure_s {
	double width, height, thickness, resolution;
	Color fcolor;
	int data_len;
	Font fonts[1000];
	int font_len, data_cap;
	Path **data;
} Figure;

/********************************************/
// Main functions for user of the library 
/********************************************/

/* Creating and editing figure */
Figure * start_figure(double width, double height);
void set_thickness_resolution(Figure * fig, double thickness, double resolution);
void set_color(Figure * fig, Color c);
void scale_figure(Figure * fig, double scale_x, double scale_y);
void resize_figure(Figure *fig, Point2D start_roi, Point2D end_roi);
void append_figures(Figure * fig1, Figure * fig2);

/* File exports and imports */
void export_eps(Figure * fig, char * file_name);
void export_svg(Figure * fig, char * file_name);
void import_svg(char * file_name, Figure ** fig);

/* Drawing functions */
void draw_fx(Figure * fig, double f(double x), double start_x, double end_x);
void draw_polyline(Figure * fig, Point2D * poly_line, int n);
void draw_circle(Figure * fig, Point2D * center, double r);
void draw_ellipse(Figure *fig, double A, double B);
void draw_binary_tree(Figure *fig, Tree * root, Point2D center);
void draw_fractal_tree(Figure *fig, double center_x, double center_y, int size, int num_iterations);
void draw_fractal_atree(Figure *fig, double center_x, double center_y, int size, int num_iterations);

/********************************************/
// Helper functions for user of the library 
/********************************************/

/* Basic getters for color and points */
Color get_color(int r, int g, int b);
Point2D get_p_full(double x, double y);
Point2D * get_p(double x, double y);

/* Some drawings */
void draw_cartesian(Figure * fig);
void draw_line(Figure *fig, Point2D sp, Point2D ep);

/* Deleting figures */
void delete_figure(Figure *fig);
