Program Prog1;
    Var a, b: Integer;
Begin
    a := 5;
    b := 7;

    While (a<b or (a>500 and b>700)) Do
    Begin
        a := a+2;
        b := 2*b;
    End

    Write (a);
    Write (b);
End.
