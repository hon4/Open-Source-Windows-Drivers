Public Class Form1

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Try
            If RadioButton2.Checked Then
                DebugCon.WriteLine(TextBox1.Text) 'Print Line with DebugCon
            Else
                DebugCon.Write(TextBox1.Text) 'Print with DebugCon
            End If
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

    End Sub
End Class
