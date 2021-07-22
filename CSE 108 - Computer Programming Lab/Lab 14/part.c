#include <stdio.h>
#include <stdlib.h>

struct Lesson
{
	char word_1[32];
	char word_2[32];
	char word_3[32];
	int num;
	double doub;
};

struct Queue
{
	struct Lesson data;
	struct Queue *next;
};

struct Lesson generate_course(char *line)
{
	struct Lesson node;
	sscanf(line, "%[^,],%[^,],%[^,],%d,%lf;", node.word_1, node.word_2, node.word_3, &(node.num), &(node.doub));
	return node;
}

void add_queue(struct Queue *lesson_queue, struct Lesson *new_lesson)
{
	struct Queue *last_node = lesson_queue;
	while(last_node -> next != NULL)
	{
		last_node = last_node -> next;
	}
	
	last_node -> next = (struct Queue *)malloc(sizeof(struct Queue));
	last_node = last_node -> next;
	(*last_node).data = *new_lesson;
}

void print_queue(struct Queue *lesson_queue, int direction)
{
	if(direction == 0)
	{
		struct Queue *node = lesson_queue;
		while(node -> next != NULL)
		{
			printf("%s, %s,%s, %d, %f\n", (*node).data.word_1, (*node).data.word_2, (*node).data.word_3, (*node).data.num, (*node).data.doub);
			node = (*node).next;
		}
	}
	else
	{
		struct Queue *node = lesson_queue;
		struct Queue *node_last = lesson_queue;
		while(node_last -> next != NULL)
		{
			node_last = (*node_last).next;
		}
		
		while(node != (*node).next)
		{
			node = lesson_queue;
			while(node -> next != node_last)
			{
				node = (*node).next;
			}
			printf("%s, %s,%s, %d, %f\n", (*node_last).data.word_1, (*node_last).data.word_2, (*node_last).data.word_3, (*node_last).data.num, (*node_last).data.doub);
			node_last = node;
		}
	}
}

void fill_queue(char filename[15], struct Queue *course_queue)
{
	char buffer[256];
	int n;
	
	FILE *fp;
	fp = fopen(filename, "r");
	
	struct Lesson item;
	while(!feof(fp))
	{
		fgets(buffer, 256, fp);
		item = generate_course(buffer);
		add_queue(course_queue, &item);
	}
	fclose(fp);
	course_queue = course_queue -> next;
	print_queue(course_queue, 1);
}

int main()
{
	struct Queue *head = (struct Queue *)malloc(sizeof(struct Queue));
	fill_queue("lab.txt", head);
}
