```
if #available(iOS 13.0, *) {
            do {
                let jsonData = try JSONSerialization.data(
                    withJSONObject: notification.request.content.userInfo,
                    options: [.withoutEscapingSlashes, .prettyPrinted]
                )

                let payload = String(data: jsonData, encoding: .utf8)
                if let string = payload?.replacingOccurrences(of: "\\", with: "") {
                    print("NOTIFICATION PAYLOAD \(string)")
                }
            } catch {
                print(error.localizedDescription)
            }
        }
```
