#include <stdio.h>
#include <math.h>
#include "vector.h"

	//========================================FUNCTIONS=======================================

double f1(double x)
{
	return sin(x / 30) * 90;
}

double f2(double x)
{
	return 1 / x;
}

double f3(double x)
{
	return tan(x);
}

void create_polyline(struct Point2D *poly_line, int poly_line_amount)
{
	for(int i = 0; i < poly_line_amount; i++)
	{
		if(i < 10)
		{
			poly_line[i].x = 20 * i - 200;
			poly_line[i].y = 10 * i * pow(-1, i);
		}
		else
		{
			poly_line[i].x = 20 * i - 200;
			poly_line[i].y = (19 - i) * i * pow(-1, i);
		}
	}
}

void create_random_binary(struct Tree *root, int turns)
{
	if(rand() % 20 > 0 && turns > 0)
	{
		(*root).right = (struct Tree *)malloc(sizeof(struct Tree));
		(*root).right -> data = rand() % 1000;
		(*root).right -> right = NULL;
		(*root).right -> left = NULL;
		create_random_binary((*root).right, turns - 1);
	}
	if(rand() % 20 > 0 && turns > 0)
	{
		(*root).left = (struct Tree *)malloc(sizeof(struct Tree));
		(*root).left -> data = rand() % 1000;
		(*root).left -> right = NULL;
		(*root).left -> left = NULL;
		create_random_binary((*root).left, turns - 1);
	}
}

	//========================================FUNCTIONS=======================================
	
	
int main()
{
	//========================================PREPARING=======================================
	srand(time(NULL));
	
	struct Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	
	struct Color red;
	red.r = 240;
	red.g = 52;
	red.b = 52;
	
	struct Color green;
	green.r = 39;
	green.g = 174;
	green.b = 96;
	
	struct Color blue;
	blue.r = 68;
	blue.g = 108;
	blue.b = 179;
	
	struct Color yellow;
	yellow.r = 250;
	yellow.g = 216;
	yellow.b = 89;
	
	struct Color orange;
	orange.r = 228;
	orange.g = 120;
	orange.b = 51;
	
	struct Color purple;
	purple.r = 155;
	purple.g = 89;
	purple.b = 182;
	
	struct Color brown;
	brown.r = 121;
	brown.g = 85;
	brown.b = 72;
	
	
	struct Point2D center;
	center.x = 0;
	center.y = 0;
	
	struct Point2D start;
	start.x = -200;
	start.y = -200;

	struct Point2D end;
	end.x = 200;
	end.y = 200;
	
	
	//The amount of poly line points
	int poly_line_amount = 20;
	struct Point2D poly_line[poly_line_amount];
	create_polyline(poly_line, poly_line_amount);
	
	//Binary tree level;
	int tree_level = 3;
	struct Tree *root = (struct Tree *)malloc(sizeof(struct Tree));
	(*root).data = rand() % 1000;
	(*root).right = NULL;
	(*root).left = NULL;
	create_random_binary(root, tree_level);
	
	//========================================PREPARING=======================================
	
	
	
	//========================================EXAMPLES========================================
	
	struct Figure *fig1 = start_figure(500, 500);
	set_thickness_resolution(fig1, 4, 1);
	set_color(fig1, black);
	draw_fx(fig1, f1, -188, 188);
	export_svg(fig1, "1_sin_graph.svg");
	export_eps(fig1, "1_sin_graph.eps");
	
	struct Figure *fig2 = start_figure(50, 50);
	set_thickness_resolution(fig2, 0.5, 0.1);
	set_color(fig2, black);
	draw_fx(fig2, f2, -50, 50);
	export_svg(fig2, "2_one_div_by_x_graph.svg");
	export_eps(fig2, "2_one_div_by_x_graph.eps");
	
	struct Figure *fig3 = start_figure(50, 50);
	set_thickness_resolution(fig3, 0.5, 0.04);
	set_color(fig3, black);
	draw_fx(fig3, f3, -50, 50);
	export_svg(fig3, "3_tan_x.svg");
	export_eps(fig3, "3_tan_x.eps");
	
	struct Figure *fig4 = start_figure(420, 360);
	set_thickness_resolution(fig4, 4, 1);
	set_color(fig4, red);
	draw_polyline(fig4, poly_line, poly_line_amount);
	export_svg(fig4, "4_polyline.svg");
	export_eps(fig4, "4_polyline.eps");
	
	struct Figure *fig5 = start_figure(480, 480);
	set_thickness_resolution(fig5, 6, 2);
	set_color(fig5, yellow);
	draw_circle(fig5, &center, 160);
	export_svg(fig5, "5_circle.svg");
	export_eps(fig5, "5_circle.eps");
	
	struct Figure *fig6 = start_figure(240, 160);
	set_thickness_resolution(fig6, 2, 0.5);
	set_color(fig6, orange);
	draw_ellipse(fig6, &center, 80, 40);
	export_svg(fig6, "6_ellipse.svg");
	export_eps(fig6, "6_ellipse.eps");
	
	struct Figure *fig7 = start_figure(960, 560);
	set_thickness_resolution(fig7, 4, 1);
	set_color(fig7, brown);
	draw_binary_tree(fig7, root);
	export_svg(fig7, "7_binary_tree.svg");
	export_eps(fig7, "7_binary_tree.eps");
	
	struct Figure *fig8 = start_figure(360, 360);
	set_thickness_resolution(fig8, 2, 2);
	set_color(fig8, blue);
	draw_koch_snowflake(fig8, &center, 2, 240, 4);
	export_svg(fig8, "8_snowflake.svg");
	export_eps(fig8, "8_snowflake.eps");
	
	struct Figure *fig9 = start_figure(480, 480);
	set_thickness_resolution(fig9, 4, 2);
	set_color(fig9, green);
	draw_fractal_tree(fig9, 0, -60, 100, 9);
	export_svg(fig9, "9_fractal_tree.svg");
	export_eps(fig9, "9_fractal_tree.eps");
	
	struct Figure *fig10 = start_figure(540, 360);
	set_thickness_resolution(fig10, 2, 8);
	set_color(fig10, purple);
	draw_fractal_atree(fig10, -90, -40, 80, 10);
	export_svg(fig10, "10_fractal_atree.svg");
	export_eps(fig10, "10_fractal_atree.eps");

	struct Figure *fig11 = start_figure(500, 500);
	set_thickness_resolution(fig11, 2, 1);
	set_color(fig11, black);
	import_svg(fig11, "3_tan_x.svg");
	scale_figure(fig11, 10, 10);
	export_svg(fig11, "11_custom_paint.svg");
	export_eps(fig11, "11_custom_paint.eps");
	
	append_figures(fig11, fig1);
	resize_figure(fig11, start, end);
	export_svg(fig11, "11.5_custom_paint.svg");
	export_eps(fig11, "11.5_custom_paint.eps");
	
	//========================================EXAMPLES========================================
}
