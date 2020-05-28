//1142 Караблин Дмитрий Курсовая на проверку
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <direct.h>

/* A coloured pixel. */

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} pixel_t;

/* A picture. */

typedef struct {
    pixel_t* pixels;
    size_t width;
    size_t height;
} bitmap_t;

/* Given "bitmap", this returns the pixel of bitmap at the point
("x", "y"). */

static pixel_t* pixel_at(bitmap_t* bitmap, int x, int y)
{
    return bitmap->pixels + bitmap->width * y + x;
}

/* Write "bitmap" to a PNG file specified by "path"; returns 0 on
success, non-zero on error. */

static int save_png_to_file(bitmap_t* bitmap, const char* path)
{
    FILE* fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte** row_pointers = NULL;
    /* "status" contains the return value of this function. At first
    it is set to a value which means 'failure'. When the routine
    has finished its work, it is set to a value which means
    'success'. */
    int status = -1;
    /* The following number is set by trial and error only. I cannot
    see where it it is documented in the libpng manual.
    */
    int pixel_size = 4;
    int depth = 8;

    fp = fopen(path, "wb");
    if (!fp) {
        goto fopen_failed;
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        goto png_create_write_struct_failed;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        goto png_create_info_struct_failed;
    }

    /* Set up error handling. */

    if (setjmp(png_jmpbuf(png_ptr))) {
        goto png_failure;
    }

    /* Set image attributes. */

    png_set_IHDR(png_ptr,
        info_ptr,
        bitmap->width,
        bitmap->height,
        depth,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);

    /* Initialize rows of PNG. */

    row_pointers = png_malloc(png_ptr, bitmap->height * sizeof(png_byte*));
    for (y = 0; y < bitmap->height; ++y) {
        png_byte* row =
            png_malloc(png_ptr, sizeof(uint8_t) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->width; ++x) {
            pixel_t* pixel = pixel_at(bitmap, x, y);
            *row++ = pixel->red;
            *row++ = pixel->green;
            *row++ = pixel->blue;
            *row++ = pixel->alpha;
        }
    }

    /* Write the image data to "fp". */

    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    /* The routine has successfully written the file, so we set
    "status" to a value which indicates success. */

    status = 0;

    for (y = 0; y < bitmap->height; y++) {
        png_free(png_ptr, row_pointers[y]);
    }
    png_free(png_ptr, row_pointers);

png_failure:
png_create_info_struct_failed:
    png_destroy_write_struct(&png_ptr, &info_ptr);
png_create_write_struct_failed:
    fclose(fp);
fopen_failed:
    return status;
}

/* Given "value" and "max", the maximum value which we expect "value"
to take, this returns an integer between 0 and 255 proportional to
"value" divided by "max". */

static int pix(int value, int max)
{
    if (value < 0)
        return 0;
    return (int)(256.0 * ((double)(value) / (double)max));
}

typedef struct
{
    int value;
    pixel_t color;
} cell;

void shuffle2d(cell** array, int n)
{
    for (int g = 0; g < 10; g++)
    {
        int j;
        for (j = 0; j < n; j++)
        {
            int i;
            for (i = 0; i < n - 1; i++)
            {
                int k = i + rand() / (RAND_MAX / (n - i) + 1);
                cell t = array[k][j];
                array[k][j] = array[i][j];
                array[i][j] = t;
            }
        }
    }
}

/* количество цветов в палитре */
#define COLORMAP__SIZE 16
float colormap[COLORMAP__SIZE][3] =
{
    /* hsv */
    {1.00000,   0.00000,   0.00000},
    {1.00000,   0.37500,   0.00000},
    {1.00000,   0.75000,   0.00000},
    {0.87500,   1.00000,   0.00000},
    {0.50000,   1.00000,   0.00000},
    {0.12500,   1.00000,   0.00000},
    {0.00000,   1.00000,   0.25000},
    {0.00000,   1.00000,   0.62500},
    {0.00000,   1.00000,   1.00000},
    {0.00000,   0.62500,   1.00000},
    {0.00000,   0.25000,   1.00000},
    {0.12500,   0.00000,   1.00000},
    {0.50000,   0.00000,   1.00000},
    {0.87500,   0.00000,   1.00000},
    {1.00000,   0.00000,   0.75000},
    {1.00000,   0.00000,   0.37500}

    /* jet */
    /*{0.00000,   0.00000,   0.75000},
    {0.00000,   0.00000,   1.00000},
    {0.00000,   0.25000,   1.00000},
    {0.00000,   0.50000,   1.00000},
    {0.00000,   0.75000,   1.00000},
    {0.00000,   1.00000,   1.00000},
    {0.25000,   1.00000,   0.75000},
    {0.50000,   1.00000,   0.50000},
    {0.75000,   1.00000,   0.25000},
    {1.00000,   1.00000,   0.00000},
    {1.00000,   0.75000,   0.00000},
    {1.00000,   0.50000,   0.00000},
    {1.00000,   0.25000,   0.00000},
    {1.00000,   0.00000,   0.00000},
    {0.75000,   0.00000,   0.00000},
    {0.50000,   0.00000,   0.00000}*/
};

float colormap_interp(float v0, float v1, float t)
{
    return t * v1 + (1.0f - t) * v0;
}
float clamp(float min, float max, float v)
{
    return fmaxf(fminf(v, max), min);
}
/* в функцию передаём значение, и границы значения.
 * Например, в value можно передавать число от 0 до 25,
 * если указывать границы min = 0, max = 25.
 * Результат, цвет RGB, будет записываться в r, g, b
 * Результат нормированный в сегменте [0, 1], поэтому
 * для использования необходимо домножить на 255. */
void colormap_rgbf(float value, float min, float max, float* r, float* g, float* b)
{
    int colors_n = COLORMAP__SIZE - 1;
    float clamped = clamp(min, max, value);
    float step = (max - min) / (float)(colors_n);

    float slot;
    float pos = modff((clamped - min) / step, &slot);

    int point1 = (int)slot;
    int point2 = point1 < colors_n ? point1 + 1 : colors_n;

    *r = colormap_interp(colormap[point1][0], colormap[point2][0], pos);
    *g = colormap_interp(colormap[point1][1], colormap[point2][1], pos);
    *b = colormap_interp(colormap[point1][2], colormap[point2][2], pos);
}

void print_array2d_index(cell** arr, int n, const char* prefix, const char* folder_name, int count)
{
    int m = 20;
    int x, y, i, j, k;
    bitmap_t fruit;
    fruit.width = n * m;
    fruit.height = n * m;
    fruit.pixels = calloc(sizeof(pixel_t), fruit.width * fruit.height);
    for (y = 0; y < fruit.height; y++)
    {
        for (x = 0; x < fruit.width; x++)
        {
            pixel_t* pixel = pixel_at(&fruit, x, y);
            pixel->red = 255;
            pixel->green = 255;
            pixel->blue = 255;
            pixel->alpha = 255;
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (x = 0; x < m; x++)
            {
                for (y = 0; y < m; y++)
                {
                    pixel_t* pixel = pixel_at(&fruit, m * i + x, m * j + y);
                    pixel->red = arr[i][j].color.red;
                    pixel->green = arr[i][j].color.green;
                    pixel->blue = arr[i][j].color.blue;
                }
            }
        }
    }

    char buf[100];
    snprintf(buf, 100, "%s/%s%06d.png", folder_name, prefix, count);
    printf("%s\n", buf);   
    save_png_to_file(&fruit, buf);
}

void ShellSort(cell** arr, int n, int k, int stop)               // * ∆k = (b∆k−1)/2  ∆0 = N
{
    int  i, y, j;
    // Выбор шага
    for (int step = n*n ; step > 0; step-- )
    // Перечисление элементов, которые сортируются на определённом шаге
        for (i = step; i < n; i++)
        // Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
            for (y = i - step; y >= 0 && arr[y][k].value > arr[y + step][k].value; y -= step)
            {
                if (stop < 0)
                   return;
                cell temp = arr[y][k];
                arr[y][k] = arr[y + step][k];
                arr[y + step][k] = temp;
                --stop;
            }
}

int main()
{
    srand(time(NULL));
    int n;
    char* folder_name[100];
    system("cls");  // очищаем экран
    printf("Welcome to the ShellSort Programm!\n");
    printf("Main options:\n");
    printf("1. Start proramm\n");
    printf("2. Show programmer\n");    
    printf("3. Exit\n");
    printf(">");
    int input;
    scanf("%d", &input);
    switch (input) {
    case 2:
        printf("Programmed by Karablin Dmitrii\n");       
    case 1:            /* обратите внимание на двоеточие, точки сзапятой тут нет */
        printf("Choose your number of values to sort\n");
        printf(">");
        while (!scanf("%d", &n))
        {
            char buf[100];
            scanf("%s", buf);
            printf("Enter an integer >");
        }
        printf("Your choice is = %d\n", n);
        printf("Enter your folder name( On English and without whitespace )\n");
        printf(">");
        scanf("%s",&folder_name);
        printf("Your choice is = %s\n", folder_name);
        _mkdir(folder_name);
        printf("Programm started...\n");
        break;    
    case 3:
        printf("Thank you for choose this programm. Good-Bye! (\n");
        return(0);
    default:
        printf("Invalid value.\n");
        exit(0);
    }  
    int i, j;
    int stop = n/10;
    int r = n, c = n;   
    cell** arr = (cell**)malloc(r * sizeof(cell*));
    for (i = 0; i < r; i++)
        arr[i] = (cell*)malloc(c * sizeof(cell));

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            arr[i][j].value = i;
            float rr, gg, bb;
            colormap_rgbf(i, 0, n, &rr, &gg, &bb);
            arr[i][j].color.red = rr * 255;
            arr[i][j].color.green = gg * 255;
            arr[i][j].color.blue = bb * 255;
        }
    }

    shuffle2d(arr, n);

    printf("\n");

    char* prefix = "fname";

    print_array2d_index(arr, n, prefix, folder_name, 0);
    for (int z = 0; z < n; z++)
    {
        for (int k = 0; k < n; k++)
        {
            ShellSort(arr, n, k, stop);            
        }
    print_array2d_index(arr, n, prefix, folder_name, z + 1);
    }
    printf("\n");
    printf("Well done!");

    for (i = 0; i < n; i++)
        free(arr[i]);
    free(arr);

    return 0;
}
