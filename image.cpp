#include "image.h"

IMG* create_img(int width, int height) {
	IMG *res = (IMG *)malloc(sizeof(IMG));
	res->width = width;
	res->height = height;
	res->mat = NULL;
	res->mat = (int **)calloc(height, sizeof(int *));
	res->mat[0] = (int *)calloc(width * height, sizeof(int));
	for(int i = 1; i < height; i++) {
		res->mat[i] = res->mat[i - 1] + width;
	}

	return res;
}

IMG* create_img2(int **mat, int width, int height) {
	IMG *res = create_img(width, height);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			res->mat[i][j] = mat[i][j];
		}
	}

	return res;
}

IMG* read_img(char *files_name) {
	FILE *in;
	char dump[128];
	int width, height, scale;

	if(!(in = fopen(files_name, "r"))) {
		printf("No se pudo abrir la imagen.\n");
		return NULL;
	}

	//Se lee el P2 o alguna otra cadena que contenga la imagen
	fscanf(in, "%s", dump);
	fscanf(in, "%d %d", &width, &height);
	fscanf(in, "%d", &scale);

	IMG *res = create_img(width, height);

	int act;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			fscanf(in, "%d", &act);
			res->mat[i][j] = act;
		}
	}

	fclose(in);

	return res;
}

void print_img(IMG *img, char *files_name) {
	FILE *out;
	out = fopen(files_name, "w");
	fprintf(out, "P2\n");
	fprintf(out, "%d %d\n255\n", img->width, img->height);

	for(int i = 0; i < img->height; i++) {
		for(int j = 0; j < img->width; j++) {
			fprintf(out, "%d\n", abs(img->mat[i][j]));
		}
	}

	fclose(out);
}

IMG* copy_img(IMG *img) {
	IMG *res = (IMG *)malloc(sizeof(IMG));
	res->width = img->width;
	res->height = img->height;
	res->mat = create_matrix(img->height, img->width, int);
	for(int i = 0; i < img->height; i++) {
		for(int j = 0; j < img->width; j++) {
			res->mat[i][j] = img->mat[i][j];
		}
	}

	return res;
}

void free_img(IMG *obj) {
	free(obj->mat[0]);
	free(obj->mat);
	free(obj);
	obj = NULL;
}

IMG* resize_img(IMG *img) {
	//Recortar la imagen
	int minX = img->width + 1, minY = img->height + 1, maxX = -1, maxY = -1;
	int act;

	for(int i = 0; i < img->height; i++) {
		for(int j = 0; j < img->width; j++) {
			act = img->mat[i][j];
			if(act != 0) {
				if(j < minX)
					minX = j;
				if(j > maxX)
					maxX = j;
				if(i < minY)
					minY = i;
				if(i > maxY)
					maxY = i;
			}
		}
	}

	int new_width = (maxX - minX + 1);
	int new_height = (maxY - minY + 1);

	IMG *res = create_img(new_width + 2, new_height + 2);

	for(int i = 0; i < res->width; i++) {
		res->mat[0][i] = res->mat[res->width - 1][i] = 0;
	}
	for(int i = 1, x = minY; i < res->height - 1; i++, x++) {
		res->mat[i][0] = res->mat[i][res->width - 1] = 0;
		for(int j = 1, y = minX; j < res->width - 1; j++, y++) {
			res->mat[i][j] = img->mat[x][y];
		}
	}
	
	return res;
}

void draw_line(IMG *img, int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    if((x0 >= 0 && x0 < img->height) &&
       (y0 >= 0 && y0 < img->width))
    	img->mat[x0][y0] = 150;
    if (abs(dx) > abs(dy)) {	// pendiente < 1
        double m = (double) dy / (double) dx;
        double b = y0 - m * x0;
        if(dx < 0)
            dx = -1;
        else
            dx = 1;
        while (x0 != x1) {
            x0 += dx;
            y0 = round(m * x0 + b);
            if((x0 >= 0 && x0 < img->height) &&
       			(y0 >= 0 && y0 < img->width))
            	img->mat[x0][y0] = 150;
        }
    }
    else if (dy != 0) {		// pendiente >= 1
        double m = (double) dx / (double) dy;
        double b = x0 - m * y0;
        if(dy < 0)
            dy = -1;
        else
            dy = 1;
        while (y0 != y1) {
            y0 += dy;
            x0 = round(m * y0 + b);
            if((x0 >= 0 && x0 < img->height) &&
       			(y0 >= 0 && y0 < img->width))
            	img->mat[x0][y0] = 150;
        }
    }
}