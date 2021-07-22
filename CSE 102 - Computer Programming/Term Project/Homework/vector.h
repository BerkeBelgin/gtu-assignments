#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265

struct Color
{
	int r;
	int g;
	int b;
};

struct Tree
{
	int data;
	struct Tree *left;
	struct Tree *right;
};

struct Point2D
{
	int x;
	int y;
};

struct Line
{
	double x1;
	double y1;
	double x2;
	double y2;
	struct Line *next;
};

struct Number
{
	int data;
	double size;
	double x;
	double y;
	struct Number *next;
};

struct Figure
{
	double width;
	double height;
	double thickness;
	double resolution;
	struct Color c;
	struct Line *line;
	struct Number *number;
};

struct Figure *start_figure(double width, double height)
{
	struct Figure *fig = (struct Figure *)malloc(sizeof(struct Figure));
	
	struct Color c;
	c.r = 0;
	c.g = 0;
	c.b = 0;
	
	(*fig).width = width;
	(*fig).height = height;
	(*fig).thickness = 0;
	(*fig).resolution = 0;
	(*fig).c = c;
	(*fig).line = NULL;
	(*fig).number = NULL;
	
	return fig;
}

void set_thickness_resolution(struct Figure *fig, double thickness, double resolution)
{
	(*fig).thickness = thickness;
	(*fig).resolution = resolution;
}

void set_color(struct Figure *fig, struct Color c)
{
	if(c.r > 255 || c.r < 0)
	{
		c.r = 0;
	}
	if(c.g > 255 || c.g < 0)
	{
		c.r = 0;
	}
	if(c.b > 255 || c.b < 0)
	{
		c.r = 0;
	}
	
	(*fig).c = c;
}

struct Line *return_last_element(struct Figure *fig)
{
	struct Line *line = (*fig).line;
	
	if(line != NULL)
	{
		while(line -> next != NULL)
		{
			line = line -> next;
		}
		return line;
	}
}

struct Number *return_last_number(struct Figure *fig)
{
	struct Number *number = (*fig).number;
	
	if(number != NULL)
	{
		while(number -> next != NULL)
		{
			number = number -> next;
		}
		return number;
	}
}

void delete_last_element(struct Figure *fig)
{
	struct Line *line = (*fig).line;
	
	if(line != NULL)
	{
		if(line -> next != NULL)
		{
			while(line -> next -> next != NULL)
			{
				line = line -> next;
			}
			free(line -> next);
			line -> next = NULL;
		}
		else
		{
			free(fig -> line);
			fig -> line = NULL;
		}
	}
}

void delete_last_number(struct Figure *fig)
{
	struct Number *number = (*fig).number;
	
	if(number != NULL)
	{
		if(number -> next != NULL)
		{
			while(number -> next -> next != NULL)
			{
				number = number -> next;
			}
			free(number -> next);
			number -> next = NULL;
		}
		else
		{
			free(fig -> number);
			fig -> number = NULL;
		}
	}
}

void draw_fx(struct Figure *fig, double f(double), double start_x, double end_x)
{
	struct Line *line = (struct Line *)malloc(sizeof(struct Line));
	struct Line *head = return_last_element(fig);
	
	if((*fig).line == NULL)(*fig).line = line;
	else(*head).next = line;
	
	double resolution = (*fig).resolution;
	double lim_rght = (*fig).width / 2;
	double lim_lft = -1 * (*fig).width / 2;
	double lim_up = (*fig).height / 2;
	double lim_dwn = -1 * (*fig).height / 2;
	
	for(double i = 0; resolution * (i + 1) <= end_x && resolution * i <= lim_rght; i++)
	{
		if(f(resolution * i) <= lim_up && f(resolution * i) >= lim_dwn
		|| f(resolution * (i + 1)) <= lim_up && f(resolution * (i + 1)) >= lim_dwn)
		{
			if(isnan(f(resolution * i)) == 0 && isnan(f(resolution * (i + 1))) == 0)
			{
				(*line).x1 = resolution * i;
				(*line).y1 = f(resolution * i);
				(*line).x2 = resolution * (i + 1);
				(*line).y2 = f(resolution * (i + 1));
				if(resolution * (i + 2) >= end_x)
				{
					(*line).x2 = end_x;
					(*line).y2 = f(end_x);
				}
				
				if(isinf((*line).y1))
				{
					if((f(resolution * (i + 1)) - f(resolution * (i + 0.5))) / (resolution * 0.5) <= 0)(*line).y1 = lim_up;
					if((f(resolution * (i + 1)) - f(resolution * (i + 0.5))) / (resolution * 0.5) > 0)(*line).y1 = lim_dwn;
				}
				if(isinf((*line).y2))
				{
					if((f(resolution * (i - 0.5)) - f(resolution * (i - 1))) / (resolution * 0.5) >= 0)(*line).y2 = lim_up;
					if((f(resolution * (i - 0.5)) - f(resolution * (i - 1))) / (resolution * 0.5) < 0)(*line).y2 = lim_dwn;
				}
				
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
			}
		}
	}
	
	for(double i = 0; resolution * (i - 1) >= start_x && resolution * i >= lim_lft; i--)
	{
		if(f(resolution * i) <= lim_up && f(resolution * i) >= lim_dwn
		|| f(resolution * (i - 1)) <= lim_up && f(resolution * (i - 1)) >= lim_dwn)
		{
			if(isnan(f(resolution * i)) == 0 && isnan(f(resolution * (i - 1))) == 0)
			{
				(*line).x1 = resolution * i;
				(*line).y1 = f(resolution * i);
				(*line).x2 = resolution * (i - 1);
				(*line).y2 = f(resolution * (i - 1));
				if(resolution * (i - 2) <= start_x)
				{
					(*line).x2 = start_x;
					(*line).y2 = f(start_x);
				}
				
				if(isinf((*line).y1))
				{
					if((f(resolution * (i - 0.5)) - f(resolution * (i - 1))) / (resolution * 0.5) > 0)(*line).y1 = lim_up;
					if((f(resolution * (i - 0.5)) - f(resolution * (i - 1))) / (resolution * 0.5) <= 0)(*line).y1 = lim_dwn;
				}
				if(isinf((*line).y2))
				{
					if((f(resolution * (i + 1)) - f(resolution * (i + 0.5))) / (resolution * 0.5) < 0)(*line).y2 = lim_up;
					if((f(resolution * (i + 1)) - f(resolution * (i + 0.5))) / (resolution * 0.5) >= 0)(*line).y2 = lim_dwn;
				}
				
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = NULL;
			}
		}
	}
	delete_last_element(fig);
}

void draw_polyline(struct Figure *fig, struct Point2D *poly_line, int n)
{
	struct Line *line = (struct Line *)malloc(sizeof(struct Line));
	struct Line *head = return_last_element(fig);
	
	if((*fig).line == NULL)(*fig).line = line;
	else(*head).next = line;
	
	for(int i = 0; i < n - 1; i++)
	{
		(*line).x1 = poly_line[i].x;
		(*line).y1 = poly_line[i].y;
		(*line).x2 = poly_line[i + 1].x;
		(*line).y2 = poly_line[i + 1].y;
		(*line).next = 	NULL;
		if(i + 1 < n - 1)
		{
			(*line).next = (struct Line *)malloc(sizeof(struct Line));
			line = (*line).next;
		}
	}
}

double f_crcl(double x, double r, double a, double b)
{
	return sqrt(pow(r, 2) - pow(x - a, 2)) + b;
}

void draw_circle(struct Figure *fig, struct Point2D *center, double r)
{
	struct Line *line = (struct Line *)malloc(sizeof(struct Line));
	struct Line *head = return_last_element(fig);
	
	if((*fig).line == NULL)(*fig).line = line;
	else(*head).next = line;
	
	double resolution = (*fig).resolution;
	double a = (*center).x;
	double b = (*center).y;
	double lim_rght = (*fig).width / 2;
	double lim_lft = -1 * (*fig).width / 2;
	double lim_up = (*fig).height / 2;
	double lim_dwn = -1 * (*fig).height / 2;
	
	for(double i = 0; resolution * i <= lim_rght; i++)
	{
		if(f_crcl(resolution * i, r, a, b) <= lim_up && -1 * f_crcl(resolution * i, r, a, b) >= lim_dwn 
		|| f_crcl(resolution * (i + 1), r, a, b) <= lim_up && -1 * f_crcl(resolution * (i + 1), r, a, b) >= lim_dwn)
		{
			if(pow(r, 2) - pow(resolution * i - a, 2) >= 0 && pow(r, 2) - pow(resolution * (i + 1) - a, 2) >= 0)
			{
				(*line).x1 = resolution * i;
				(*line).y1 = f_crcl(resolution * i, r, a, b);
				(*line).x2 = resolution * (i + 1);
				(*line).y2 = f_crcl(resolution * (i + 1), r, a, b);
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
				
				(*line).x1 = resolution * i;
				(*line).y1 = -1 * f_crcl(resolution * i, r, a, b) + 2 * b;
				(*line).x2 = resolution * (i + 1);
				(*line).y2 = -1 * f_crcl(resolution * (i + 1), r, a, b) + 2 * b;
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
			}
		}
	}
	for(double i = 0; resolution * i >= lim_lft; i--)
	{
		if(f_crcl(resolution * i, r, a, b) <= lim_up && -1 * f_crcl(resolution * i, r, a, b) >= lim_dwn 
		|| f_crcl(resolution * (i - 1), r, a, b) <= lim_up && -1 * f_crcl(resolution * (i - 1), r, a, b) >= lim_dwn)
		{
			if(pow(r, 2) - pow(resolution * i - a, 2) >= 0 && pow(r, 2) - pow(resolution * (i - 1) - a, 2) >= 0)
			{
				(*line).x1 = resolution * i;
				(*line).y1 = f_crcl(resolution * i, r, a, b);
				(*line).x2 = resolution * (i - 1);
				(*line).y2 = f_crcl(resolution * (i - 1), r, a, b);
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
				
				(*line).x1 = resolution * i;
				(*line).y1 = -1 * f_crcl(resolution * i, r, a, b) + 2 * b;
				(*line).x2 = resolution * (i - 1);
				(*line).y2 = -1 * f_crcl(resolution * (i - 1), r, a, b) + 2 * b;
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
			}
		}
	}
	delete_last_element(fig);
}

double f_ellps(double x, double r_a, double r_b, double a, double b)
{
	return sqrt((1 - pow(x - a, 2) / pow(r_a, 2)) * pow(r_b, 2)) + b;
}

void draw_ellipse(struct Figure *fig, struct Point2D *center, double r_x, double r_y)
{
	struct Line *line = (struct Line *)malloc(sizeof(struct Line));
	struct Line *head = return_last_element(fig);
	
	if((*fig).line == NULL)(*fig).line = line;
	else(*head).next = line;
	
	double resolution = (*fig).resolution;
	double r_a = r_x;
	double r_b = r_y;
	double a = (*center).x;
	double b = (*center).y;
	double lim_rght = (*fig).width / 2;
	double lim_lft = -1 * (*fig).width / 2;
	double lim_up = (*fig).height / 2;
	double lim_dwn = -1 * (*fig).height / 2;
	
	for(double i = 0; resolution * i <= lim_rght; i++)
	{
		if(f_ellps(resolution * i, r_a, r_b, a, b) <= lim_up && -1 * f_ellps(resolution * i, r_a, r_b, a, b) >= lim_dwn
		|| f_ellps(resolution * (i + 1), r_a, r_b, a, b) <= lim_up && -1 * f_ellps(resolution * (i + 1), r_a, r_b, a, b) >= lim_dwn)
		{
			if((1 - pow(resolution * i - a, 2) / pow(r_a, 2)) * pow(r_b, 2) >= 0 && (1 - pow(resolution * (i + 1) - a, 2) / pow(r_a, 2)) * pow(r_b, 2) >= 0)
			{
				(*line).x1 = resolution * i;
				(*line).y1 = f_ellps(resolution * i, r_a, r_b, a, b);
				(*line).x2 = resolution * (i + 1);
				(*line).y2 = f_ellps(resolution * (i + 1), r_a, r_b, a, b);
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
				
				(*line).x1 = resolution * i;
				(*line).y1 = -1 * f_ellps(resolution * i, r_a, r_b, a, b) + 2 * b;
				(*line).x2 = resolution * (i + 1);
				(*line).y2 = -1 * f_ellps(resolution * (i + 1), r_a, r_b, a, b) + 2 * b;
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
			}
		}
	}
	for(double i = 0; resolution * i >= lim_lft; i--)
	{
		if(f_ellps(resolution * i, r_a, r_b, a, b) <= lim_up && -1 * f_ellps(resolution * i, r_a, r_b, a, b) >= lim_dwn
		|| f_ellps(resolution * (i - 1), r_a, r_b, a, b) <= lim_up && - 1* f_ellps(resolution * (i - 1), r_a, r_b, a, b) >= lim_dwn)
		{
			if((1 - pow(resolution * i - a, 2) / pow(r_a, 2)) * pow(r_b, 2) >= 0 && (1 - pow(resolution * (i - 1) - a, 2) / pow(r_a, 2)) * pow(r_b, 2) >= 0)
			{
				(*line).x1 = resolution * i;
				(*line).y1 = f_ellps(resolution * i, r_a, r_b, a, b);
				(*line).x2 = resolution * (i - 1);
				(*line).y2 = f_ellps(resolution * (i - 1), r_a, r_b, a, b);
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
				
				(*line).x1 = resolution * i;
				(*line).y1 = -1 * f_ellps(resolution * i, r_a, r_b, a, b) + 2 * b;
				(*line).x2 = resolution * (i - 1);
				(*line).y2 = -1 * f_ellps(resolution * (i - 1), r_a, r_b, a, b) + 2 * b;
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
			}
		}
	}
	delete_last_element(fig);
}

void binary_tree(struct Figure *fig, struct Tree *root, struct Point2D center, int r,double size, double shift_x, double shift_y)
{
	if((*root).right != NULL)
	{
		struct Line *line = (struct Line *)malloc(sizeof(struct Line));
		struct Line *head = return_last_element(fig);
		(*head).next = line;
		
		struct Number *number = (struct Number *)malloc(sizeof(struct Number));
		struct Number *head2 = return_last_number(fig);
		(*head2).next = number;
		
		struct Point2D center_c;
		center_c.x = center.x + shift_x;
		center_c.y = center.y - shift_y;
		
		(*line).x1 = center_c.x;
		(*line).y1 = center_c.y + r;
		(*line).x2 = center.x + cos(PI / 3) * r;
		(*line).y2 = center.y - sin(PI / 3) * r;
		(*line).next = NULL;
		
		if((*root).right -> data >= 0 && (*root).right -> data <= 999)(*number).data = (*root).right -> data;
		else(*number).data = -1;
		(*number).size = size;
		(*number).x = center_c.x;
		(*number).y = center_c.y;
		(*number).next = NULL;
		
		draw_circle(fig, &center_c, r);
		binary_tree(fig, (*root).right, center_c, r, size, shift_x * 0.5, shift_y);
	}
	if((*root).left != NULL)
	{
		struct Line *line = (struct Line *)malloc(sizeof(struct Line));
		struct Line *head = return_last_element(fig);
		(*head).next = line;
		
		struct Number *number = (struct Number *)malloc(sizeof(struct Number));
		struct Number *head2 = return_last_number(fig);
		(*head2).next = number;
		
		struct Point2D center_c;
		center_c.x = center.x - shift_x;
		center_c.y = center.y - shift_y;
		
		(*line).x1 = center_c.x;
		(*line).y1 = center_c.y + r;
		(*line).x2 = center.x - cos(PI / 3) * r;
		(*line).y2 = center.y - sin(PI / 3) * r;
		(*line).next = NULL;
		
		if((*root).left -> data >= 0 && (*root).left -> data <= 999)(*number).data = (*root).left -> data;
		else(*number).data = -1;
		(*number).size = size;
		(*number).x = center_c.x;
		(*number).y = center_c.y;
		(*number).next = NULL;
		
		draw_circle(fig, &center_c, r);
		binary_tree(fig, (*root).left, center_c, r, size, shift_x * 0.5, shift_y);
	}
}

void find_depth(struct Tree *root,int i, int *n)
{
	if((*root).right != NULL)
	{
		find_depth((*root).right, i + 1, n);
	}
	if((*root).left != NULL)
	{
		find_depth((*root).left, i + 1, n);
	}
	
	if(i > *n)
	{
		*n = i;
	}
}

void draw_binary_tree(struct Figure *fig, struct Tree *root)
{
	if(root != NULL)
	{
		int depth = 0;
		find_depth(root, 1, &depth);
		
		int r = 180 / (depth + 2);
		double size = r * 0.8;
		double shift_x = (*fig).width * 0.22;
		double shift_y = r * 3;
		
		struct Number *number = (struct Number *)malloc(sizeof(struct Number));
		struct Number *head = return_last_number(fig);
		
		if((*fig).number == NULL)(*fig).number = number;
		else(*head).next = number;
		
		struct Point2D center;
		center.x = 0;
		center.y = ((*fig).height / 2) * 0.6;
		
		if((*root).data >= 0 && (*root).data <= 999)(*number).data = (*root).data;
		else(*number).data = -1;
		(*number).size = size;
		(*number).x = center.x;
		(*number).y = center.y;
		(*number).next = NULL;
		
		draw_circle(fig, &center, r);
		binary_tree(fig, root, center, r, size, shift_x, shift_y);
	}
}

void scale_figure(struct Figure *fig, double scale_x, double scale_y)
{
	struct Line *line = (*fig).line;
	while(line != NULL)
	{
		(*line).x1 *= scale_x;
		(*line).y1 *= scale_y;
		(*line).x2 *= scale_x;
		(*line).y2 *= scale_y;
		line = (*line).next;
	}
	
	struct Number *number = (*fig).number;
	while(number != NULL)
	{
		(*number).x *= scale_x;
		(*number).y *= scale_y;
		number = (*number).next;
	}
}

void resize_figure(struct Figure *fig, struct Point2D start_roi, struct Point2D end_roi)
{
	struct Point2D new_center;
	double center_x = (end_roi.x + start_roi.x) / 2;
	double center_y = (end_roi.y + start_roi.y) / 2;
	
	double x_shift = -1 * center_x;
	double y_shift = -1 * center_y;
	
	(*fig).width = abs(end_roi.x - start_roi.x);
	(*fig).height = abs(end_roi.y - start_roi.y);
	
	struct Line *line = (*fig).line;
	while(line != NULL)
	{
		(*line).x1 += x_shift;
		(*line).y1 += y_shift;
		(*line).x2 += x_shift;
		(*line).y2 += y_shift;
		line = (*line).next;
	}
	
	struct Number *number = (*fig).number;
	while(number != NULL)
	{
		(*number).x += x_shift;
		(*number).y += y_shift;
		number = (*number).next;
	}
}

void append_figures(struct Figure *fig1, struct Figure * fig2)
{
	struct Line *line = (*fig2).line;
	struct Line *head = return_last_element(fig1);
	
	if((*fig1).line == NULL)(*fig1).line = line;
	else(*head).next = line;
	
	struct Number *number = (*fig2).number;
	struct Number *head2 = return_last_number(fig1);
	
	if((*fig1).number == NULL)(*fig1).number = number;
	else(*head2).next = number;
}

void koch_snowflake(struct Figure *fig, struct Point2D *center, double thickness, int size, int num_iterations)
{
	if(num_iterations > 0)
	{
		if((*fig).line == NULL)
		{
			struct Line *line = (struct Line *)malloc(sizeof(struct Line));
			(*fig).line = line;
		
			double points[4][2] = 
			{
				(*center).x - size / (2 * sqrt(3)), (*center).y + size / 2,
				(*center).x + size / sqrt(3), (*center).y,
				(*center).x - size / (2 * sqrt(3)), (*center).y - size / 2,
				(*center).x - size / (2 * sqrt(3)), (*center).y + size / 2
			};
			
			for(int i = 0; i < 3; i++)
			{
				(*line).x1 = points[i][0];
				(*line).y1 = points[i][1];
				(*line).x2 = points[i + 1][0];
				(*line).y2 = points[i + 1][1];
				(*line).next = 	NULL;
				
				if(i + 1 < 3)
				{
					(*line).next = (struct Line *)malloc(sizeof(struct Line));
					line = (*line).next;
				}
			}
		}
		else
		{
			struct Line *line = (*fig).line;
			struct Line *line_next;
			double points[5][2];
			
			while(line != NULL)
			{
				line_next = line -> next;
				
				points[0][0] = (*line).x1;
				points[0][1] = (*line).y1;
				points[4][0] = (*line).x2;
				points[4][1] = (*line).y2;
				points[1][0] = ((*line).x2 + 2 * (*line).x1) / 3;
				points[1][1] = ((*line).y2 + 2 * (*line).y1) / 3;
				points[3][0] = (2 * (*line).x2 + (*line).x1) / 3;
				points[3][1] = (2 * (*line).y2 + (*line).y1) / 3;
				points[2][0] = cos(atan2(points[3][1] - points[1][1], points[3][0] - points[1][0]) + PI / 3) * size + points[1][0];
				points[2][1] = sin(atan2(points[3][1] - points[1][1], points[3][0] - points[1][0]) + PI / 3) * size + points[1][1];
				
				for(int i = 0; i < 4; i++)
				{
					(*line).x1 = points[i][0];
					(*line).y1 = points[i][1];
					(*line).x2 = points[i + 1][0];
					(*line).y2 = points[i + 1][1];
					(*line).next = 	NULL;
					
					if(i + 1 < 4)
					{
						(*line).next = (struct Line *)malloc(sizeof(struct Line));
						line = (*line).next;
					}
				}
				
				(*line).next = line_next;
				line = (*line).next;
			}
		}
		koch_snowflake(fig, center, thickness, size / 3, num_iterations - 1);
	}
}

void draw_koch_snowflake(struct Figure *fig, struct Point2D *center, double thickness, int size, int num_iterations)
{
	(*fig).thickness = thickness;
	
	struct Figure *fig2 = start_figure((*fig).width, (*fig).height);
	set_thickness_resolution(fig2, (*fig).thickness, (*fig).resolution);
	set_color(fig2, (*fig).c);
	koch_snowflake(fig2, center, thickness, size, num_iterations);
	append_figures(fig, fig2);
}

void fractal_tree(struct Figure *fig, double center_x, double center_y, int size, int num_iterations)
{
	if(num_iterations > 0)
	{
		if((*fig).line == NULL)
		{
			struct Line *line = (struct Line *)malloc(sizeof(struct Line));
			(*fig).line = line;
		
			(*line).x1 = center_x;
			(*line).y1 = center_y - ((double) size * 1.5);
			(*line).x2 = center_x;
			(*line).y2 = center_y - ((double) size * 1.5) + size;
			(*line).next = 	NULL;
			
			fractal_tree(fig, center_x, center_y, size * 0.75, num_iterations - 1);
		}
		else
		{
			struct Line *line = (struct Line *)malloc(sizeof(struct Line));
			struct Line *head = return_last_element(fig);
			(*head).next = line;
			
			(*line).x1 = (*head).x2;
			(*line).y1 = (*head).y2;
			(*line).x2 = (*head).x2 + cos(atan2((*head).y2 - (*head).y1, (*head).x2 - (*head).x1) + PI / 7) * size;
			(*line).y2 = (*head).y2 + sin(atan2((*head).y2 - (*head).y1, (*head).x2 - (*head).x1) + PI / 7) * size;
			(*line).next = 	NULL;
			
			fractal_tree(fig, center_x, center_y, size * 0.75, num_iterations - 1);
			
			line = return_last_element(fig);
			(*line).next = (struct Line *)malloc(sizeof(struct Line));
			line = (*line).next;
			
			(*line).x1 = (*head).x2;
			(*line).y1 = (*head).y2;
			(*line).x2 = (*head).x2 + cos(atan2((*head).y2 - (*head).y1, (*head).x2 - (*head).x1) - PI / 7) * size;
			(*line).y2 = (*head).y2 + sin(atan2((*head).y2 - (*head).y1, (*head).x2 - (*head).x1) - PI / 7) * size;
			(*line).next = 	NULL;
			
			fractal_tree(fig, center_x, center_y, size * 0.75, num_iterations - 1);
		}
	}
}

void draw_fractal_tree(struct Figure *fig, double center_x, double center_y, int size, int num_iterations)
{
	struct Figure *fig2 = start_figure((*fig).width, (*fig).height);
	set_thickness_resolution(fig2, (*fig).thickness, (*fig).resolution);
	set_color(fig2, (*fig).c);
	fractal_tree(fig2, center_x, center_y, size, num_iterations);
	append_figures(fig, fig2);
}

void fractal_atree(struct Figure *fig, double center_x, double center_y, int size, int num_iterations)
{
	if(num_iterations > 0)
	{
		if((*fig).line == NULL)
		{
			struct Line *line = (struct Line *)malloc(sizeof(struct Line));
			(*fig).line = line;
		
			(*line).x1 = center_x;
			(*line).y1 = center_y - ((double) size * 1.5);
			(*line).x2 = center_x;
			(*line).y2 = center_y - ((double) size * 1.5) + size;
			(*line).next = 	NULL;
			
			fractal_atree(fig, center_x, center_y, size * 0.75, num_iterations - 1);
		}
		else
		{
			struct Line *line = (struct Line *)malloc(sizeof(struct Line));
			struct Line *head = return_last_element(fig);
			(*head).next = line;
			
			(*line).x1 = (*head).x2;
			(*line).y1 = (*head).y2;
			(*line).x2 = (*head).x2 + cos(atan2((*head).y2 - (*head).y1, (*head).x2 - (*head).x1) + PI * 0.1) * size;
			(*line).y2 = (*head).y2 + sin(atan2((*head).y2 - (*head).y1, (*head).x2 - (*head).x1) + PI * 0.1) * size;
			(*line).next = 	NULL;
			
			fractal_atree(fig, center_x, center_y, size * 0.75, num_iterations - 1);
			
			line = return_last_element(fig);
			(*line).next = (struct Line *)malloc(sizeof(struct Line));
			line = (*line).next;
			
			(*line).x1 = (*head).x2;
			(*line).y1 = (*head).y2;
			(*line).x2 = (*head).x2 + cos(atan2((*head).y2 - (*head).y1, (*head).x2 - (*head).x1) - PI * 0.2) * size;
			(*line).y2 = (*head).y2 + sin(atan2((*head).y2 - (*head).y1, (*head).x2 - (*head).x1) - PI * 0.2) * size;
			(*line).next = 	NULL;
			
			fractal_atree(fig, center_x, center_y, size * 0.75, num_iterations - 1);
		}
	}
}

void draw_fractal_atree(struct Figure *fig, double center_x, double center_y, int size, int num_iterations)
{
	struct Figure *fig2 = start_figure((*fig).width, (*fig).height);
	set_thickness_resolution(fig2, (*fig).thickness, (*fig).resolution);
	set_color(fig2, (*fig).c);
	fractal_atree(fig2, center_x, center_y, size, num_iterations);
	append_figures(fig, fig2);
}

void import_svg(struct Figure *fig ,char *file_name)
{
	FILE *fp;
	fp = fopen(file_name, "r");
	if(fp != NULL)
	{
		struct Line *line = (struct Line *)malloc(sizeof(struct Line));
		struct Line *head = return_last_element(fig);
		if((*fig).line == NULL)(*fig).line = line;
		else(*head).next = line;
		line -> next = NULL;
		
		struct Number *number = (struct Number *)malloc(sizeof(struct Number));
		struct Number *head2 = return_last_number(fig);
		if((*fig).number == NULL)(*fig).number = number;
		else(*head2).next = number;
		number -> next = NULL;
		
		char buffer[256];
		char word[32];
		
		char cmnd[12];
		double value;
		
		char s_line[] = "line";
		char s_x1[] = "x1";
		char s_y1[] = "y1";
		char s_x2[] = "x2";
		char s_y2[] = "y2";
		
		char s_text[] = "text";
		char s_x[] = "x";
		char s_y[] = "y";
		char s_font_size[] = "font-size";
		int data;
		
		char s_svg[] = "svg";
		char s_width[] = "width";
		char s_height[] = "height";
		
		double fig_width = (*fig).width / 2;
		double fig_height = (*fig).height / 2;
		
		
		fgets(buffer, 256, fp);
		sscanf(buffer, "<%s", word);
		
		if(!strcmp(word, s_svg))
		{
			sscanf(buffer, "<%s %[^>]", word, buffer);
			
			int n;
			do
			{
				n = sscanf(buffer, "%s%[^\n]", word, buffer);
				sscanf(word, "%[^=\"]=\"%lf\"", cmnd, &value);
				
				if(!strcmp(cmnd, s_width))fig_width = value;
				if(!strcmp(cmnd, s_height))fig_height = value;
			}
			while(n > 1);
		}
		
		while(!feof(fp))
		{
			fgets(buffer, 256, fp);
			sscanf(buffer, "%*[^<]<%s", word);
			
			if(!strcmp(word, s_line))
			{
				(*line).x1 = 0;
				(*line).y1 = 0;
				(*line).x2 = 0;
				(*line).y2 = 0;
				
				sscanf(buffer, "%*[^<]<%s %[^/>]", word, buffer);
				//printf("%s\n", buffer);
				
				int n;
				do
				{
					n = sscanf(buffer, "%s%[^\n]", word, buffer);
					sscanf(word, "%[^=\"]=\"%lf\"", cmnd, &value);
					
					if(!strcmp(cmnd, s_x1))(*line).x1 = value - fig_width / 2;
					if(!strcmp(cmnd, s_y1))(*line).y1 = value * -1 + fig_height / 2;
					if(!strcmp(cmnd, s_x2))(*line).x2 = value - fig_width / 2;
					if(!strcmp(cmnd, s_y2))(*line).y2 = value * -1 + fig_height / 2;
				}
				while(n > 1);
				
				(*line).next = (struct Line *)malloc(sizeof(struct Line));
				line = (*line).next;
				(*line).next = 	NULL;
			}
			if(!strcmp(word, s_text))
			{
				(*number).data = -1;
				(*number).size = 1;
				(*number).x = 0;
				(*number).y = 0;
				(*number).next = NULL;
				
				sscanf(buffer, "%*[^<]<%*s %[^>]>%d", buffer, &data);
				//printf("%s\n", buffer);
				//printf("%d\n", data);
				
				(*number).data = data;
				int n;
				do
				{
					n = sscanf(buffer, "%s%[^\n]", word, buffer);
					sscanf(word, "%[^=\"]=\"%lf\"", cmnd, &value);
					
					if(!strcmp(cmnd, s_x))(*number).x = value - fig_width / 2;
					if(!strcmp(cmnd, s_y))(*number).y = value - fig_height / 2;
					if(!strcmp(cmnd, s_font_size))
					{
						(*number).size = value;
						(*number).y = ((*number).y - (*number).size / 3) * -1;
					}
				}
				while(n > 1);
				
				(*number).next = (struct Number *)malloc(sizeof(struct Number));
				number = (*number).next;
				(*number).next = NULL;
			}
		}
		delete_last_element(fig);
		delete_last_number(fig);
	}
	fclose(fp);
}

void export_svg(struct Figure *fig, char * file_name)
{
	FILE *fp;
	fp = fopen(file_name, "w");
	if(fp != NULL)
	{
		fprintf(fp, "<svg version=\"1.1\" xmlns=\"https://www.w3.org/2000/svg\" width=\"%.2f\" height=\"%.2f\">\n", (*fig).width, (*fig).height);
		struct Line *line = (*fig).line;
		while(line != NULL)
		{
			//printf("x1:%.2f, y1:%.2f, x2:%.2f, y2:%.2f\n", (*line).x1, (*line).y1, (*line).x2, (*line).y2);
			fprintf(fp, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%.2f\"/>\n", 
			(*line).x1 + (*fig).width / 2, (*line).y1 * -1 + (*fig).height / 2, (*line).x2 + (*fig).width / 2, (*line).y2 * -1 + (*fig).height / 2,(*fig).c.r ,(*fig).c.g ,(*fig).c.b , (*fig).thickness);
			line = line -> next;
		}
		
		struct Number *number = (*fig).number;
		while(number != NULL)
		{
			//printf("data:%d x:%.2f y:%.2f\n", (*number).data, (*number).x, (*number).y);
			if((*number).data != -1)fprintf(fp, "\t<text x=\"%.2f\" y=\"%.2f\" font-size=\"%.2f\" fill=\"rgb(%d,%d,%d)\" text-anchor=\"middle\">%d</text>\n", (*number).x + (*fig).width / 2, ((*number).y * -1 + (*fig).height / 2) + (*number).size / 3, (*number).size, (*fig).c.r, (*fig).c.g, (*fig).c.b, (*number).data);
			number = number -> next;
		}
		fprintf(fp, "</svg>");
	}
	fclose(fp);
}


void export_eps(struct Figure *fig, char * file_name)
{
	FILE *fp;
	fp = fopen(file_name, "w");
	if(fp != NULL)
	{
		fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
		fprintf(fp ,"%%%%BoundingBox: %.2f %.2f %.2f %.2f\n", -1 * (*fig).width / 2, -1 * (*fig).height / 2, (*fig).width / 2, (*fig).height / 2);
		fprintf(fp, "%.2f setlinewidth\n", (*fig).thickness);
		fprintf(fp, "%.1f %.1f %.1f setrgbcolor\n", (double)(*fig).c.r / 255, (double)(*fig).c.g / 255, (double)(*fig).c.b / 255);
		struct Line *line = (*fig).line;
		while(line != NULL)
		{
			//printf("x1:%.2f, y1:%.2f, x2:%.2f, y2:%.2f\n", (*line).x1, (*line).y1, (*line).x2, (*line).y2);		
			fprintf(fp, "%.2f %.2f moveto\n", (*line).x1, (*line).y1);
			fprintf(fp, "%.2f %.2f rlineto\n", (*line).x2 - (*line).x1, (*line).y2 - (*line).y1);
			line = line -> next;
		}
		
		struct Number *number = (*fig).number;
		if(number != NULL)
		{
			fprintf(fp, "/show-ctr {\n");
			fprintf(fp, "  dup stringwidth pop\n");
			fprintf(fp, "  -2 div 0\n");
			fprintf(fp, "  rmoveto show\n");
			fprintf(fp, "} def\n");
			fprintf(fp, "/Times-Roman %.2f selectfont\n", (*number).size);
			while(number != NULL)
			{
				//printf("data:%d x:%.2f y:%.2f\n", (*number).data, (*number).x, (*number).y);
				if((*number).data != -1)
				{
					fprintf(fp, "%.2f %.2f moveto (%d) show-ctr\n", (*number).x, (*number).y - (*number).size / 3, (*number).data);
				}
				number = number -> next;
			}
		}
		fprintf(fp, "stroke\n");
	}
	fclose(fp);
}
