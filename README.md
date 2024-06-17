# kmr-m6制御システム
近藤科学の6脚ロボkmr-m6をesp32で、ワイヤレスで制御したかったのでarduinoで書きました。

# 実装されている機能
- ble-uart (スマホから操作する用)
- ics関係 (謎通信規格のシリアルサーボを制御する用)
- dabble（スマホにゲームパッドを表示し、bluetoothで操作するやつ）

# 反省
全てを作り直すべきではなかった。モーションの制御系は近藤科学の基板を流用し、Bluetoothモジュールだけを自作するのが労力的に正解だった。