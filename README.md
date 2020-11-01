# Strongly_Regular_Graph
Determining the Strongly Regular Graph
Документация к программе "Определение сильно-регулярного графа и его параметров"
Выполнил:
 Цибилев Олег Дмитриевич
 группа 20161

Постановка задачи:
	Для заданного графа Г = (V,E) требуется определить, является ли он сильно-регулярным графом.
	В случае положительного ответа: 
	1) вывести его параметры: 
	   (v,k,λ,μ) - (кол-во вершин, регулярность, число общих соседей для двух смежных вершин, число общих соседей для двух несмежных вершин);
	2) вывести его массив пересечений;
	3) вывести его собственные значения и их кратности.

Теоретический подход, используемый при решении:
	Определение.
	 Пусть Г = (V,E) — регулярный граф с v вершинами и степенью k. Говорят, что Г является сильно-регулярным, если существуют целые λ и μ такие, что:
	- Любые две смежные вершины имеют λ общих соседей,
	- Любые две несмежные вершины имеют μ общих соседей.
	Используемый подход опирается на следующий критерий:
	Теорема.
	 Пусть Г = (V,E) - обыкновенный граф порядка v, не являющийся полным и безрёберным, и A = A(Г) - его матрица смежности.
	Тогда следующие три условия эквивалентны:
	1) Г - сильно-регулярный граф с параметрами (v,k,λ,μ);
	2) A^2 = (λ - μ)*A + (K - μ)*I + μ*J, где I - единичная матрица, а J - матрица, состоящая из единиц;
	3) Г - регулярный граф, имеющий ровно 3 различных собственных значения.
	 Заметим также, что пустой граф; полный граф; и граф, являющийся объединением m полных графов одного порядка 
	являются сильно-регулярными графами (тривиальными сильно-регулярными графами).
	 Описание алгоритма:
	1) Предполагаем, что заданный граф является сильно-регулярным графом;
	2) Выбрав произвольным образом 3 вершины графа: v1, v2, v3, такие, что: v2 смежна с v1; v3 смежна с v2 и несмежна с v1
	   (т.е. вершина v2 находится в сфере S1(v1), а вершина v3 в сфере S2(v1) в слоевом представлении графа, начинающегося с вершины v1);
	3) Вычисляем параметры предполагаемого сильно-регулярного графа при помощи выбранных вершин и соотношения на параметры:
	   λ = a1; μ = c2 , где a1 и c2 - элементы массива пересечений;
	4) Проверяем второе условие из теоремы:
	   в случае его выполнения - 
			{
			исходный граф является сильно-регулярным (поскольку это достаточное условие)
			переходим к следующему пункту
			}
	   в противном случае - 
			{
			исходный граф не является сильно-регулярным (поскольку это необходимое условие)
			завершаем алгоритм
			};
	5) Вычисляем массив пересечений: {b0 = k, b1 = k - 1 - λ; c1 = 1, c2 = μ};
	6) Вычисляем собственные значения и их кратности, исходя из третьего условия теоремы и следующих соотношений:
	   a) Первое собственное значение - k кратности 1, т.к. граф является k-регулярным
	   b) Оставшиеся собственные значения - τ и σ являются корнями уравнения x^2 - (λ - μ)*x + (μ - k) с кратностями
	      m1 = ((n − 1)*τ + k) / (τ − σ) и m2 = n - 1 - m1 соответственно.

Программные решения:
	1) Реализован класс матриц Matrix и операции над ними, необходимые для работы с матрицей смежности графа;
	2) Реализована функция Strongly_Regular_Graph, определяющая формат входных данных:
		a) Граф задаётся в виде его матрицы смежности, чтение матрицы происходит из файла с заданным именем.
		   В первой строке файла задаётся число вершин в графе, в последующих строках - элементы матрицы смежности.
		   Пример входных данных - содержимое файла input.txt:
			5
			0 1 0 0 1
			1 0 1 0 0
			0 1 0 1 0
			0 0 1 0 1
			1 0 0 1 0
		b) Граф задаётся в виде его матрицы смежности, чтение матрицы происходит из командной строки посредством запросов к пользователю
		c) Граф задаётся в виде его списка смежности, чтение списка происходит из файла с заданным именем.
		   В первой строке файла задаётся число вершин в графе, в последующих строках - элементы списка смежности.
		   Пример входных данных - содержимое файла input.txt:
			5
			1 2
			1 5
			2 3
			3 4
			4 5
		d) Граф задаётся в виде его списка смежности, чтение списка происходит из командной строки посредством запросов к пользователю.
		   !Ввод элементов списка смежности удобнее осуществлять парами номеров вершин, разделёнными нажатием Enter, подобно примеру из предыдущего пункта!
		   !!!ДЛЯ ЗАВЕРШЕНИЯ ВВОДА ЭЛЕМЕНТОВ СПИСКА НЕОБХОДИМО ВВЕСТИ 0!!!
		   Пример ввода входных данных:
			1 2
			1 5
			2 3
			3 4
			4 5
			0
	3) Реализована функция SRGraph, реализующая алгоритм, описанный в теоретическом подходе, с дополнительными проверками.
	   SRGraph:
	   a) Проверяется, является ли заданный граф пустым;
	   b) Проверяется, является ли заданный граф полным;
	   с) Проверяется, является ли заданный граф k - регулярным;
	   d) Осуществляется поиск вершины v2 (см. Описание алгоритма пункт 2). 
	      Если такая вершина не найдена, то граф является несвязным и не является объединением полных графов => граф не сильно-регулярен;
	   e) Осуществляется поиск вершины v3 (см. Описание алгоритма пункт 2). 
	      Если такая вершина не найдена, то граф является объединением полных графов => граф сильно-регулярен;
	   f) Вычисляются параметры λ и μ и проверяется соотношение на параметры: v = 1 + k + (k*(k - 1 - λ) / μ);
	   g) Вычисляется и проверяется выражение из второго пункта Теоремы;
	   h) Вычисляется массив пересечений и собственные значения графа (см. Описание алгоритма пункты 5 и 6)
