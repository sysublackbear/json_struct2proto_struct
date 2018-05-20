# json_struct2proto_struct
带层次结构的json转换成proto。

比如下图的json结构：
```c++
{
  "foo": 1,
  "bar": "bar",
}
```

可以转换成：
```c++
message TestInfo
{
  optional int32 foo = 1 [json_key="/foo"];
  optional BarInfo bar_info = 2;
}

message BarInfo
{
  optional bytes bar = 1 [json_key="/bar"];
}
```
利用protobuf和Json的反射特性。
