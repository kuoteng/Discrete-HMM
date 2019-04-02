#! /bin/bash
./train 10 model_init.txt seq_model_01.txt ./results/model_01-10.txt
./train 10 model_init.txt seq_model_02.txt ./results/model_02-10.txt
./train 10 model_init.txt seq_model_03.txt ./results/model_03-10.txt
./train 10 model_init.txt seq_model_04.txt ./results/model_04-10.txt
./train 10 model_init.txt seq_model_05.txt ./results/model_05-10.txt
./test ./results/modellist-10.txt testing_data1.txt result1.txt

./train 50 model_init.txt seq_model_01.txt ./results/model_01-50.txt
./train 50 model_init.txt seq_model_02.txt ./results/model_02-50.txt
./train 50 model_init.txt seq_model_03.txt ./results/model_03-50.txt
./train 50 model_init.txt seq_model_04.txt ./results/model_04-50.txt
./train 50 model_init.txt seq_model_05.txt ./results/model_05-50.txt
./test ./results/modellist-50.txt testing_data1.txt result1.txt

./train 100 model_init.txt seq_model_01.txt ./results/model_01-100.txt
./train 100 model_init.txt seq_model_02.txt ./results/model_02-100.txt
./train 100 model_init.txt seq_model_03.txt ./results/model_03-100.txt
./train 100 model_init.txt seq_model_04.txt ./results/model_04-100.txt
./train 100 model_init.txt seq_model_05.txt ./results/model_05-100.txt
./test ./results/modellist-100.txt testing_data1.txt result1.txt

./train 500 model_init.txt seq_model_01.txt ./results/model_01-500.txt
./train 500 model_init.txt seq_model_02.txt ./results/model_02-500.txt
./train 500 model_init.txt seq_model_03.txt ./results/model_03-500.txt
./train 500 model_init.txt seq_model_04.txt ./results/model_04-500.txt
./train 500 model_init.txt seq_model_05.txt ./results/model_05-500.txt
./test ./results/modellist-500.txt testing_data1.txt result1.txt

./train 1126 model_init.txt seq_model_01.txt ./results/model_01-1126.txt
./train 1126 model_init.txt seq_model_02.txt ./results/model_02-1126.txt
./train 1126 model_init.txt seq_model_03.txt ./results/model_03-1126.txt
./train 1126 model_init.txt seq_model_04.txt ./results/model_04-1126.txt
./train 1126 model_init.txt seq_model_05.txt ./results/model_05-1126.txt
./test ./results/modellist-1126.txt testing_data1.txt result1.txt

./train 3000 model_init.txt seq_model_01.txt ./results/model_01-3000.txt
./train 3000 model_init.txt seq_model_02.txt ./results/model_02-3000.txt
./train 3000 model_init.txt seq_model_03.txt ./results/model_03-3000.txt
./train 3000 model_init.txt seq_model_04.txt ./results/model_04-3000.txt
./train 3000 model_init.txt seq_model_05.txt ./results/model_05-3000.txt
./test ./results/modellist-3000.txt testing_data1.txt result1.txt

./train 5000 model_init.txt seq_model_01.txt ./results/model_01-5000.txt
./train 5000 model_init.txt seq_model_02.txt ./results/model_02-5000.txt
./train 5000 model_init.txt seq_model_03.txt ./results/model_03-5000.txt
./train 5000 model_init.txt seq_model_04.txt ./results/model_04-5000.txt
./train 5000 model_init.txt seq_model_05.txt ./results/model_05-5000.txt
./test ./results/modellist-5000.txt testing_data1.txt result1.txt
