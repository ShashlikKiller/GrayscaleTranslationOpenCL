# Программа для перевода изображения в градации серого
### Проект содержит несколько методов по переводу цветного изображения в градации серого.

## Стэк используемых технологий:

###### **C++** [*18.3*]
###### **OpenCV** [*4.8*]
###### **OpenCL** [*3.0 from CUDA DevKit*]
###### **Concurrency** [*namespace*]

## Реализованные методы:

* **getGrayPtr(Изображение)**:
##### *Работает сразу со всей строкой изображения, что позволяет сократить расчетное время перевода из трех каналов пикселя в одну градацию белого;*
* **getGrayPtrParallel_for(Изображение)**:
##### *Также, как и getGrayPtr(Изображение), работает со строкой вместо отдельных пикселей, но использует лямбда-функцию parallel_for;*
* **getGrayByEveryPixel(Изображение)**:
##### *Переводит каждый пиксель изображения в градации серого без параллелизма;*
* **grayscaleOnKernel(int[][][] МатрицаКаналовИзображения)**:
##### *Переводит трехмерную матрицу к одномерному типу, после чего над ней совершаются точно такие же вычисления, как и в host-методах, но с использованием GPGPU вычислений.*

## Запуск приложения:
* С передачей вашего изображения в качестве аргумента:
##### start GrayscaleTranslationOpenCL.exe ../[*Папка, в котором находится ваше изображение*]/[*Имя изображения*].[*Формат изображения*]
###### *OpenCV позволяет работать практически со всеми существующими форматами хранения изображения.*
* Без передачи изображения в качестве аргумента:
##### start GrayscaleTranslationOpenCL.exe
###### *В этом случае программа возьмет тестовое изображение, которое хранится в проекте.*
 
