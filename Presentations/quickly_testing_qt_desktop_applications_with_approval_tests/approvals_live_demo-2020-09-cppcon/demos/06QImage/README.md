# 06 QImage

## Images

* Run the Images test
    * Note how Araxis Merge says the approved image is corrupt
* Run again with BeyondCompare
    * Note how the "approved" image is 1 byte
* It's not convenient to approve image outputs
    * Could auto-approve with `ApprovalTests::AutoApproveReporter`
    * Or use `ApprovalTests::ClipboardReporter` and then paste the command in to a console window and run
