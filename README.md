# 1072_圖形理論 GRAPH THEORY Project 

## Chinese Postman Problem (無向圖)

## (一)演算法思路/解題邏輯

  核心問題為找出Euler Circuit，即可得出最短路徑結果。

  但若graphy存在奇數degree的vertex，則必須先兩兩maching並找出最短路徑，將Edge加至graph方能求解Euler Circuit。


## (二)程式碼解釋/程式碼實作

  依程式運行流程解釋各function功能與方法

### 1.利用NetworkManager::intrepret. 進行讀檔(./file/topo.txt)，並建立拓樸。

### 2.void inputdata(); 將拓譜存入自建的資料結構。

### 3.bool FindOddVertex(); 找出所有奇數degree的vertex。

### 4.void FindShortPath(); 利用Path::find_paths找出任兩點的任何路徑(非最短)。

### 5.vector<string> GetShortPath(); 計算可找出任兩點"最短"路徑。

### 6.void CalculateShortestPath(); 將所有奇數degree的vertex以""窮舉法""找出所有maching。

### 7.int matching(); 從所有maching中挑選出"路徑最短的matching"。

### 8.void AddEdge(); 將matching的Edge結果加入graph。

### 9.vector<VERTEX *> Hierholzer(); 利用"Hierholzers Algorithm"解無向圖的Euler Circuit。

### 詳細的解法為:
  
### (1)從任一點出發，開始走回至原點的Circuit( 未包含全部Edge )，並放入Stack
  
### (2)由Stack開始往回探索所有vertex，並找尋是否還有別的路徑能走，並放入Stack
  
### (3)持續尋找直到Stack中所有Vertex都找不到其他路徑( 已含全部Edge )

### 10.得出結果print出solution.txt

## (三)執行結果

### 1.程式運行方式: 執行"bash ./run.sh"

### 2.輸出結果: 產生solution.txt於當下路徑

